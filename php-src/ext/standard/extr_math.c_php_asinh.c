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
 scalar_t__ M_E ; 
 double asinh (double) ; 
 double log (scalar_t__) ; 
 int pow (double,int) ; 
 scalar_t__ sqrt (int) ; 

__attribute__((used)) static double php_asinh(double z)
{
#ifdef HAVE_ASINH
	return(asinh(z));
#else
# ifdef _WIN64
	if (z >= 0) {
		return log(z + sqrt(z * z + 1));
	}
	else {
		return -log(-z + sqrt(z * z + 1));
	}
# else
	return(log(z + sqrt(1 + pow(z, 2))) / log(M_E));
# endif
#endif
}