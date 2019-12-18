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
struct TYPE_3__ {size_t num_dead_tuples; size_t max_dead_tuples; int /*<<< orphan*/ * dead_tuples; } ;
typedef  TYPE_1__ LVRelStats ;
typedef  int /*<<< orphan*/ * ItemPointer ;

/* Variables and functions */
 int /*<<< orphan*/  PROGRESS_VACUUM_NUM_DEAD_TUPLES ; 
 int /*<<< orphan*/  pgstat_progress_update_param (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
lazy_record_dead_tuple(LVRelStats *vacrelstats,
					   ItemPointer itemptr)
{
	/*
	 * The array shouldn't overflow under normal behavior, but perhaps it
	 * could if we are given a really small maintenance_work_mem. In that
	 * case, just forget the last few tuples (we'll get 'em next time).
	 */
	if (vacrelstats->num_dead_tuples < vacrelstats->max_dead_tuples)
	{
		vacrelstats->dead_tuples[vacrelstats->num_dead_tuples] = *itemptr;
		vacrelstats->num_dead_tuples++;
		pgstat_progress_update_param(PROGRESS_VACUUM_NUM_DEAD_TUPLES,
									 vacrelstats->num_dead_tuples);
	}
}