#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int count; unsigned int* list; } ;
struct sigmadsp {TYPE_1__ rate_constraints; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int sigmadsp_rate_to_index(struct sigmadsp *sigmadsp, unsigned int rate)
{
	unsigned int i;

	for (i = 0; i < sigmadsp->rate_constraints.count; i++) {
		if (sigmadsp->rate_constraints.list[i] == rate)
			return i;
	}

	return -EINVAL;
}