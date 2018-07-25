#include<cstdio>
#include<math.h>
#include <iostream>

using namespace std;

// a function pricing call option
double binomialCallPrice(int timeToMaturityInMonths, double strike, double sigma, double interestRate, double spotStockPrice, int numSteps)
{

  double dt = 1./numSteps;
  double u = exp(sigma * sqrt(dt));
  double d = 1./u;
  double discount = exp(-interestRate*dt);
  double p1 = ( exp(interestRate*dt) - d) / (u - d);
  double p2 = 1.-p1;
  int numStepsToMaturity = (int) round( (double)timeToMaturityInMonths / 12. * (double)numSteps );
  int numPrice = numStepsToMaturity + 1;
  double callPrice[numPrice];

// price at maturity
  for(int i=0; i<numPrice; i++){
     double stockPrice = spotStockPrice * pow(u, numStepsToMaturity - 2*i);
     if(stockPrice>strike){
        callPrice[i] = stockPrice - strike;
     }else{
        callPrice[i]=0.;
     }
  }

// propagate backward
  for(int j=numStepsToMaturity-1; j>=0; j--){  
    for(int i=0; i<=j; i++){
      callPrice[i] = (p1 * callPrice[i] + p2 * callPrice[i+1]) * discount;
    }
  }

  return callPrice[0];

}

// a function computing put price based on call-put parity
double CallToPut (double callPrice0, int timeToMaturityInMonths, double strike, double interestRate, double spotStockPrice) 
{

  double putPrice = callPrice0 + strike*exp(-interestRate*timeToMaturityInMonths/12.) - spotStockPrice;
  return putPrice;

}


int main()
{

  int Nmonths=6;
  double strike=10.;
  double spotStockPrice=10.;
  double sigma=0.3;
  double interestRate=0.03;
  int numSteps=100;

  cin >> Nmonths;
  cin >> strike;
  cin >> spotStockPrice;
  cin >> sigma;
  cin >> interestRate;
  cin >> numSteps;
  printf("sigma = %f \n", sigma);
  printf("interestRate = %f \n", interestRate);
  printf("numSteps = %d \n", numSteps);

  double binomial_call_price=0., binomial_put_price=0.;

  binomial_call_price = binomialCallPrice(Nmonths, strike, sigma, interestRate, spotStockPrice, numSteps);
  binomial_put_price = CallToPut(binomial_call_price, Nmonths, strike, interestRate, spotStockPrice);

  printf("Binomial European Call Price = %f \n", binomial_call_price);
  printf("Binomial European Put Price = %f \n", binomial_put_price);

}

