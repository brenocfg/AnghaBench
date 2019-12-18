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
struct task_struct {int state; } ;
struct TYPE_2__ {int /*<<< orphan*/  block_start; int /*<<< orphan*/  sleep_start; } ;
struct sched_entity {TYPE_1__ statistics; } ;
struct cfs_rq {struct sched_entity* curr; } ;

/* Variables and functions */
 int DEQUEUE_SLEEP ; 
 int TASK_INTERRUPTIBLE ; 
 int TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __schedstat_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ entity_is_task (struct sched_entity*) ; 
 int /*<<< orphan*/  rq_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_of (struct cfs_rq*) ; 
 int /*<<< orphan*/  schedstat_enabled () ; 
 struct task_struct* task_of (struct sched_entity*) ; 
 int /*<<< orphan*/  update_stats_wait_end (struct cfs_rq*,struct sched_entity*) ; 

__attribute__((used)) static inline void
update_stats_dequeue(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
{

	if (!schedstat_enabled())
		return;

	/*
	 * Mark the end of the wait period if dequeueing a
	 * waiting task:
	 */
	if (se != cfs_rq->curr)
		update_stats_wait_end(cfs_rq, se);

	if ((flags & DEQUEUE_SLEEP) && entity_is_task(se)) {
		struct task_struct *tsk = task_of(se);

		if (tsk->state & TASK_INTERRUPTIBLE)
			__schedstat_set(se->statistics.sleep_start,
				      rq_clock(rq_of(cfs_rq)));
		if (tsk->state & TASK_UNINTERRUPTIBLE)
			__schedstat_set(se->statistics.block_start,
				      rq_clock(rq_of(cfs_rq)));
	}
}