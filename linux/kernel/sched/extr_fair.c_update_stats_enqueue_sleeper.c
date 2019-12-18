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
typedef  int u64 ;
struct task_struct {scalar_t__ in_iowait; } ;
struct TYPE_2__ {int /*<<< orphan*/  iowait_count; int /*<<< orphan*/  iowait_sum; int /*<<< orphan*/  sum_sleep_runtime; int /*<<< orphan*/  block_start; int /*<<< orphan*/  block_max; int /*<<< orphan*/  sleep_start; int /*<<< orphan*/  sleep_max; } ;
struct sched_entity {TYPE_1__ statistics; } ;
struct cfs_rq {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ SLEEP_PROFILING ; 
 int /*<<< orphan*/  __schedstat_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __schedstat_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __schedstat_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  account_scheduler_latency (struct task_struct*,int,int) ; 
 scalar_t__ entity_is_task (struct sched_entity*) ; 
 scalar_t__ get_wchan (struct task_struct*) ; 
 scalar_t__ prof_on ; 
 int /*<<< orphan*/  profile_hits (scalar_t__,void*,int) ; 
 int rq_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_of (struct cfs_rq*) ; 
 int /*<<< orphan*/  schedstat_enabled () ; 
 int schedstat_val (int /*<<< orphan*/ ) ; 
 struct task_struct* task_of (struct sched_entity*) ; 
 int /*<<< orphan*/  trace_sched_stat_blocked (struct task_struct*,int) ; 
 int /*<<< orphan*/  trace_sched_stat_iowait (struct task_struct*,int) ; 
 int /*<<< orphan*/  trace_sched_stat_sleep (struct task_struct*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void
update_stats_enqueue_sleeper(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	struct task_struct *tsk = NULL;
	u64 sleep_start, block_start;

	if (!schedstat_enabled())
		return;

	sleep_start = schedstat_val(se->statistics.sleep_start);
	block_start = schedstat_val(se->statistics.block_start);

	if (entity_is_task(se))
		tsk = task_of(se);

	if (sleep_start) {
		u64 delta = rq_clock(rq_of(cfs_rq)) - sleep_start;

		if ((s64)delta < 0)
			delta = 0;

		if (unlikely(delta > schedstat_val(se->statistics.sleep_max)))
			__schedstat_set(se->statistics.sleep_max, delta);

		__schedstat_set(se->statistics.sleep_start, 0);
		__schedstat_add(se->statistics.sum_sleep_runtime, delta);

		if (tsk) {
			account_scheduler_latency(tsk, delta >> 10, 1);
			trace_sched_stat_sleep(tsk, delta);
		}
	}
	if (block_start) {
		u64 delta = rq_clock(rq_of(cfs_rq)) - block_start;

		if ((s64)delta < 0)
			delta = 0;

		if (unlikely(delta > schedstat_val(se->statistics.block_max)))
			__schedstat_set(se->statistics.block_max, delta);

		__schedstat_set(se->statistics.block_start, 0);
		__schedstat_add(se->statistics.sum_sleep_runtime, delta);

		if (tsk) {
			if (tsk->in_iowait) {
				__schedstat_add(se->statistics.iowait_sum, delta);
				__schedstat_inc(se->statistics.iowait_count);
				trace_sched_stat_iowait(tsk, delta);
			}

			trace_sched_stat_blocked(tsk, delta);

			/*
			 * Blocking time is in units of nanosecs, so shift by
			 * 20 to get a milliseconds-range estimation of the
			 * amount of time that the task spent sleeping:
			 */
			if (unlikely(prof_on == SLEEP_PROFILING)) {
				profile_hits(SLEEP_PROFILING,
						(void *)get_wchan(tsk),
						delta >> 20);
			}
			account_scheduler_latency(tsk, delta >> 10, 0);
		}
	}
}