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
 double exp (double) ; 
 double expm1 (double) ; 

__attribute__((used)) static double php_expm1(double x)
{
#ifndef PHP_WIN32
	return(expm1(x));
#else
	return(exp(x) - 1);
#endif
}