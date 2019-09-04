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
typedef  double double_t ;

/* Variables and functions */
 double pS0 ; 
 double pS1 ; 
 double pS2 ; 
 double pS3 ; 
 double pS4 ; 
 double pS5 ; 
 double qS1 ; 
 double qS2 ; 
 double qS3 ; 
 double qS4 ; 

__attribute__((used)) static double R(double z)
{
	double_t p, q;
	p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
	q = 1.0+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
	return p/q;
}