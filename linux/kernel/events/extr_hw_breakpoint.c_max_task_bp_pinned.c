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
typedef  enum bp_type_idx { ____Placeholder_bp_type_idx } bp_type_idx ;
struct TYPE_2__ {unsigned int* tsk_pinned; } ;

/* Variables and functions */
 TYPE_1__* get_bp_info (int,int) ; 
 int* nr_slots ; 

__attribute__((used)) static unsigned int max_task_bp_pinned(int cpu, enum bp_type_idx type)
{
	unsigned int *tsk_pinned = get_bp_info(cpu, type)->tsk_pinned;
	int i;

	for (i = nr_slots[type] - 1; i >= 0; i--) {
		if (tsk_pinned[i] > 0)
			return i + 1;
	}

	return 0;
}