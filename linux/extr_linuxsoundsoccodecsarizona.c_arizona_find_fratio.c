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
 TYPE_1__* fll_fratios ; 

__attribute__((used)) static int arizona_find_fratio(unsigned int Fref, int *fratio)
{
	int i;

	/* Find an appropriate FLL_FRATIO */
	for (i = 0; i < ARRAY_SIZE(fll_fratios); i++) {
		if (fll_fratios[i].min <= Fref && Fref <= fll_fratios[i].max) {
			if (fratio)
				*fratio = fll_fratios[i].fratio;
			return fll_fratios[i].ratio;
		}
	}

	return -EINVAL;
}