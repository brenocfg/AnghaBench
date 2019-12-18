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
typedef  scalar_t__ GucSource ;

/* Variables and functions */
 scalar_t__ PGC_S_INTERACTIVE ; 
 void* malloc (int) ; 

bool
check_random_seed(double *newval, void **extra, GucSource source)
{
	*extra = malloc(sizeof(int));
	if (!*extra)
		return false;
	/* Arm the assign only if source of value is an interactive SET */
	*((int *) *extra) = (source >= PGC_S_INTERACTIVE);

	return true;
}