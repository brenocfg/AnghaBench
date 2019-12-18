#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 double KernelBessel_J1 (double) ; 
 float KernelBessel_P1 (double) ; 
 float KernelBessel_Q1 (double) ; 
 double M_PI ; 
 float cos (double) ; 
 float sin (double) ; 
 float sqrt (float) ; 

__attribute__((used)) static double KernelBessel_Order1(double x)
{
	double p, q;

	if (x == 0.0)
		return (0.0f);
	p = x;
	if (x < 0.0)
		x=(-x);
	if (x < 8.0)
		return (p*KernelBessel_J1(x));
	q = (double)sqrt(2.0f/(M_PI*x))*(double)(KernelBessel_P1(x)*(1.0f/sqrt(2.0f)*(sin(x)-cos(x)))-8.0f/x*KernelBessel_Q1(x)*
		(-1.0f/sqrt(2.0f)*(sin(x)+cos(x))));
	if (p < 0.0f)
		q = (-q);
	return (q);
}