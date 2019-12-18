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
typedef  scalar_t__ u64 ;
struct thread_runtime {scalar_t__ ready_to_run; scalar_t__ last_time; scalar_t__ last_state; scalar_t__ dt_preempt; int /*<<< orphan*/  total_preempt_time; scalar_t__ dt_iowait; int /*<<< orphan*/  total_iowait_time; scalar_t__ dt_sleep; int /*<<< orphan*/  total_sleep_time; scalar_t__ dt_delay; int /*<<< orphan*/  total_delay_time; scalar_t__ dt_run; int /*<<< orphan*/  total_run_time; int /*<<< orphan*/  run_stats; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 scalar_t__ TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void timehist_update_runtime_stats(struct thread_runtime *r,
					 u64 t, u64 tprev)
{
	r->dt_delay   = 0;
	r->dt_sleep   = 0;
	r->dt_iowait  = 0;
	r->dt_preempt = 0;
	r->dt_run     = 0;

	if (tprev) {
		r->dt_run = t - tprev;
		if (r->ready_to_run) {
			if (r->ready_to_run > tprev)
				pr_debug("time travel: wakeup time for task > previous sched_switch event\n");
			else
				r->dt_delay = tprev - r->ready_to_run;
		}

		if (r->last_time > tprev)
			pr_debug("time travel: last sched out time for task > previous sched_switch event\n");
		else if (r->last_time) {
			u64 dt_wait = tprev - r->last_time;

			if (r->last_state == TASK_RUNNING)
				r->dt_preempt = dt_wait;
			else if (r->last_state == TASK_UNINTERRUPTIBLE)
				r->dt_iowait = dt_wait;
			else
				r->dt_sleep = dt_wait;
		}
	}

	update_stats(&r->run_stats, r->dt_run);

	r->total_run_time     += r->dt_run;
	r->total_delay_time   += r->dt_delay;
	r->total_sleep_time   += r->dt_sleep;
	r->total_iowait_time  += r->dt_iowait;
	r->total_preempt_time += r->dt_preempt;
}