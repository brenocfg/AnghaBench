#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int min; unsigned int max; int fratio; int ratio; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* fll_sync_fratios ; 

__attribute__((used)) static int madera_find_sync_fratio(unsigned int fref, int *fratio)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(fll_sync_fratios); i++) {
		if (fll_sync_fratios[i].min <= fref &&
		    fref <= fll_sync_fratios[i].max) {
			if (fratio)
				*fratio = fll_sync_fratios[i].fratio;

			return fll_sync_fratios[i].ratio;
		}
	}

	return -EINVAL;
}