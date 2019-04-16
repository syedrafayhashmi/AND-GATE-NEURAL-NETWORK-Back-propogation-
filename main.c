#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include<windows.h>

#define inputno  3
#define num_pattern  4
#define hiddennums 4

const int numitteration = 50;
const double LR_InHidden = 0.7;
const double LR_HiddenOut = 0.1;
int patNum = 0;
double errThisPat = 0.0;
double outPred = 0.0;
double RMSerror = 0.0;

double hiddenVal[hiddennums];
double weightsIH[inputno][hiddennums];
double weightsHO[hiddennums];

int trainInputs[num_pattern][inputno];
int trainOutput[num_pattern];

void calcNet(void)
{   
    int i = 0;
    for(i = 0;i<hiddennums;i++)
    {
	  hiddenVal[i] = 0.0;

        for(int j = 0;j<inputno;j++)
        {
	   hiddenVal[i] = hiddenVal[i] + (trainInputs[patNum][j] * weightsIH[j][i]);
        }

        hiddenVal[i] = tanh(hiddenVal[i]);
    }   
   outPred = 0.0;
   for(i = 0;i<hiddennums;i++)
   {
    outPred = outPred + hiddenVal[i] * weightsHO[i];
   }
    errThisPat = outPred - trainOutput[patNum];
}
void WeightHO(void)
{
   for(int k = 0;k<hiddennums;k++)
   {
    double weightChange = LR_HiddenOut * errThisPat * hiddenVal[k];
    weightsHO[k] = weightsHO[k] - weightChange;

   if (weightsHO[k] < -5)
    {
     weightsHO[k] = -5;
    }
    else if (weightsHO[k] > 5)
    {
     weightsHO[k] = 5;
    }
   }

 }
 
void WeightIH(void)
{

  for(int i = 0;i<hiddennums;i++)
  {
   for(int k = 0;k<inputno;k++)
   {
    double x = 1 - (hiddenVal[i] * hiddenVal[i]);
    x = x * weightsHO[i] * errThisPat * LR_InHidden;
    x = x * trainInputs[patNum][k];
    double weightChange = x;
    weightsIH[k][i] = weightsIH[k][i] - weightChange;
   }
  }
}
double getRand(void)
{
 return ((double)rand())/(double)RAND_MAX;
}

void initWght(void)
{

 for(int j = 0;j<hiddennums;j++)
 {
    weightsHO[j] = (getRand() - 0.5)/2;
    for(int i = 0;i<inputno;i++)
    {
     weightsIH[i][j] = (getRand() - 0.5)/5;
     printf("Weight = %f\n", weightsIH[i][j]);
    }
  }
}

void initData(void)
{
    printf("Initialising Data.....\n");
    Sleep(1200);
    trainInputs[0][0]  = 1;
    trainInputs[0][1]  = -1;
    trainInputs[0][2]  = 1;  
    trainOutput[0] = 0;

    trainInputs[1][0]  = -1;
    trainInputs[1][1]  = 1;
    trainInputs[1][2]  = 1;  
    trainOutput[1] = 0;

    trainInputs[2][0]  = 1;
    trainInputs[2][1]  = -1;
    trainInputs[2][2]  = 1;  
    trainOutput[2] = 0;

    trainInputs[3][0]  = -1;
    trainInputs[3][1]  = -1;
    trainInputs[3][2]  = 1;  
    trainOutput[3] = 1;
 }

void ShowOutput(void)
{
 for(int i = 0;i<num_pattern;i++)
 {
  patNum = i;
  calcNet();
  printf("Pattern Number = %d Desired Output = %d Output of Neural Network = %f\n"
  ,patNum+1,trainOutput[patNum],outPred);
 }
}



void OverallError(void)
{
     RMSerror = 0.0;
     for(int i = 0;i<num_pattern;i++)
        {
         patNum = i;
         calcNet();
         RMSerror = RMSerror + (errThisPat * errThisPat);
        }
     RMSerror = RMSerror/num_pattern;
     RMSerror = sqrt(RMSerror);
}




int main(void)
{
 
 srand ( time(NULL) );
 
 initWght();
 initData();
 printf("**********Syed Rafay Hashmi EL-17098 SEC C*****************\n");
 printf("***********ARTIFICIAL NEURAL NETWORK OF AND GATE***********\n");
    for(int j = 0;j <= numitteration;j++)
    {
        for(int i = 0;i<num_pattern;i++)
        {
          patNum = rand()%num_pattern;
          calcNet();         
          WeightHO();
          WeightIH();
        }
        OverallError();
        printf(" Error Correction Itteration Number %d RMS Error = %f\n",j,RMSerror);
        Sleep(200);
        
    } 
 ShowOutput();
 
 system("PAUSE");
 return 0;
}
