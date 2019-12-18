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
struct sched_gate_list {int /*<<< orphan*/  base_time; int /*<<< orphan*/  cycle_time_extension; scalar_t__ cycle_time; } ;
struct sched_entry {scalar_t__ interval; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ get_cycle_time_elapsed (struct sched_gate_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ktime_t get_interval_end_time(struct sched_gate_list *sched,
				     struct sched_gate_list *admin,
				     struct sched_entry *entry,
				     ktime_t intv_start)
{
	s32 cycle_elapsed = get_cycle_time_elapsed(sched, intv_start);
	ktime_t intv_end, cycle_ext_end, cycle_end;

	cycle_end = ktime_add_ns(intv_start, sched->cycle_time - cycle_elapsed);
	intv_end = ktime_add_ns(intv_start, entry->interval);
	cycle_ext_end = ktime_add(cycle_end, sched->cycle_time_extension);

	if (ktime_before(intv_end, cycle_end))
		return intv_end;
	else if (admin && admin != sched &&
		 ktime_after(admin->base_time, cycle_end) &&
		 ktime_before(admin->base_time, cycle_ext_end))
		return admin->base_time;
	else
		return cycle_end;
}