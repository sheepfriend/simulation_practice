#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double max(double a,double b){
	if(a>=b){return a;}
	else{return b;}
}

void generate(double result[1000][6]){
	int i,j,number=1000;
	for(i=0;i<number;i++){
		if(i==0){result[i][0]=(double)(rand()%10000)/10000;}
		else{result[i][0]=(double)(rand()%10000)/10000+result[i-1][0];}
		result[i][1]=(double)(rand()%10000)/10000;
		if(i==0){result[i][4]=0;}
		result[i][2]=max(result[i][0],result[i][4]);
		result[i][3]=result[i][2]+result[i][1];
		if(i<number-1){result[i+1][4]=result[i][3];}
		result[i][5]=result[i][4]-result[i][0];
	}
	printf("%f\n",result[0][0]);
}

double waiting_mean(double table[1000][6]){
	double sum=0;
	int i;
	for(i=0;i<1000;i++){
		if(table[i][5]>0){sum=sum+table[i][5];}
	}
	sum=sum/1000;
	return sum;
}

double spare_sum(double table[1000][6]){
	double sum=0;
	int i;
	for(i=0;i<1000;i++){
		if(table[i][5]<0){sum=sum-table[i][5];}
	}
	return sum;
}

void queue(double table[1000][6],double result[4000][2]){
	int i=0,j=0,k=0;
	while(i<1000 && j<1000){
		while(i<1000 && table[i][0]<table[j][4]){
			result[k][0]=table[i][0];
			if(k==0){result[k][1]=0;}
			else{result[k][1]=result[k-1][1];}
			k++;
			result[k][0]=table[i][0];
			result[k][1]=result[k-1][1]+1;
			i++;
			k++;
			if(i>=1000){
				while(j<1000){
					result[k][0]=table[j][4];
					result[k][1]=result[k][1];
					k++;
					result[k][0]=table[j][4];
					result[k][1]=result[k][1]-1;					k++;
					j++;
				}
			}
		}
		while(j<1000 && table[i][0]>table[j][4]){
			result[k][0]=table[j][4];
			if(k==0){result[k][1]=0;}
			else{result[k][1]=result[k-1][1];}
			k++;
			result[k][0]=table[j][4];
			result[k][1]=result[k-1][1]-1;
			j++;
			k++;
			if(j>=1000){
				while(i<1000){
					result[k][0]=table[i][0];
					result[k][1]=result[k][1];
					k++;
					result[k][0]=table[i][0];
					result[k][1]=result[k][1]-1;					k++;
					j++;
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	double record[1000][6];
	double result[4000][2];
	srand((unsigned)time(NULL));
	generate(record);
	queue(record,result);
	printf("%f\n",waiting_mean(record));
	printf("%f\n",spare_sum(record));
/*	for(int i=0;i<1000;i++){
		for(int j=0;j<6;j++){
			printf("%f ",record[i][j]);
		}
		printf("\n");
	}*/
	return 0;
}