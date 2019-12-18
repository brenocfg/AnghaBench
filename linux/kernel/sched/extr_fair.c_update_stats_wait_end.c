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
typedef  scalar_t__ u64 ;
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait_start; int /*<<< orphan*/  wait_sum; int /*<<< orphan*/  wait_count; int /*<<< orphan*/  wait_max; } ;
struct sched_entity {TYPE_1__ statistics; } ;
struct cfs_rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __schedstat_add (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __schedstat_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __schedstat_set (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ entity_is_task (struct sched_entity*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ rq_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_of (struct cfs_rq*) ; 
 int /*<<< orphan*/  schedstat_enabled () ; 
 scalar_t__ schedstat_val (int /*<<< orphan*/ ) ; 
 struct task_struct* task_of (struct sched_entity*) ; 
 scalar_t__ task_on_rq_migrating (struct task_struct*) ; 
 int /*<<< orphan*/  trace_sched_stat_wait (struct task_struct*,scalar_t__) ; 

__attribute__((used)) static inline void
update_stats_wait_end(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	struct task_struct *p;
	u64 delta;

	if (!schedstat_enabled())
		return;

	delta = rq_clock(rq_of(cfs_rq)) - schedstat_val(se->statistics.wait_start);

	if (entity_is_task(se)) {
		p = task_of(se);
		if (task_on_rq_migrating(p)) {
			/*
			 * Preserve migrating task's wait time so wait_start
			 * time stamp can be adjusted to accumulate wait time
			 * prior to migration.
			 */
			__schedstat_set(se->statistics.wait_start, delta);
			return;
		}
		trace_sched_stat_wait(p, delta);
	}

	__schedstat_set(se->statistics.wait_max,
		      max(schedstat_val(se->statistics.wait_max), delta));
	__schedstat_inc(se->statistics.wait_count);
	__schedstat_add(se->statistics.wait_sum, delta);
	__schedstat_set(se->statistics.wait_start, 0);
}