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
struct gcov_info {TYPE_1__* counts; } ;
struct TYPE_2__ {unsigned int num; scalar_t__* values; } ;

/* Variables and functions */
 unsigned int num_counter_active (struct gcov_info*) ; 

void gcov_info_add(struct gcov_info *dest, struct gcov_info *source)
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < num_counter_active(dest); i++) {
		for (j = 0; j < dest->counts[i].num; j++) {
			dest->counts[i].values[j] +=
				source->counts[i].values[j];
		}
	}
}