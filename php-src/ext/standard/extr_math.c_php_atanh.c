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
 double atanh (double) ; 
 double log (int) ; 

__attribute__((used)) static double php_atanh(double z)
{
#ifdef HAVE_ATANH
	return(atanh(z));
#else
	return(0.5 * log((1 + z) / (1 - z)));
#endif
}