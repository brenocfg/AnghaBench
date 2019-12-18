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
 double log (int) ; 
 double log1p (double) ; 

__attribute__((used)) static double php_log1p(double x)
{
#ifdef HAVE_LOG1P
	return(log1p(x));
#else
	return(log(1 + x));
#endif
}