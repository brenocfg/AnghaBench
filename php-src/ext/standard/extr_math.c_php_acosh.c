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
 double ZEND_NAN ; 
 double acosh (double) ; 
 double log (scalar_t__) ; 
 scalar_t__ sqrt (double) ; 

__attribute__((used)) static double php_acosh(double x)
{
#ifdef HAVE_ACOSH
	return(acosh(x));
#else
# ifdef _WIN64
	if (x >= 1) {
		return log(x + sqrt(x * x - 1));
	} else {
		return ZEND_NAN;
	}
# else
	return(log(x + sqrt(x * x - 1)));
# endif
#endif
}