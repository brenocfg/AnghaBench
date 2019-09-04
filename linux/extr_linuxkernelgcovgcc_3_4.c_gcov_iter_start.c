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
struct gcov_iterator {size_t num_types; TYPE_1__* type_info; int /*<<< orphan*/  info; scalar_t__ count; scalar_t__ type; scalar_t__ function; scalar_t__ record; } ;
struct TYPE_2__ {int ctr_type; scalar_t__ offset; } ;

/* Variables and functions */
 int GCOV_COUNTERS ; 
 scalar_t__ counter_active (int /*<<< orphan*/ ,int) ; 

void gcov_iter_start(struct gcov_iterator *iter)
{
	int i;

	iter->record = 0;
	iter->function = 0;
	iter->type = 0;
	iter->count = 0;
	iter->num_types = 0;
	for (i = 0; i < GCOV_COUNTERS; i++) {
		if (counter_active(iter->info, i)) {
			iter->type_info[iter->num_types].ctr_type = i;
			iter->type_info[iter->num_types++].offset = 0;
		}
	}
}