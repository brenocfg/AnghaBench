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
struct sched_entity {scalar_t__ on_rq; } ;
struct cfs_rq {int /*<<< orphan*/ * curr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __enqueue_entity (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  check_cfs_rq_runtime (struct cfs_rq*) ; 
 int /*<<< orphan*/  check_spread (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  update_curr (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_load_avg (struct cfs_rq*,struct sched_entity*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stats_wait_start (struct cfs_rq*,struct sched_entity*) ; 

__attribute__((used)) static void put_prev_entity(struct cfs_rq *cfs_rq, struct sched_entity *prev)
{
	/*
	 * If still on the runqueue then deactivate_task()
	 * was not called and update_curr() has to be done:
	 */
	if (prev->on_rq)
		update_curr(cfs_rq);

	/* throttle cfs_rqs exceeding runtime */
	check_cfs_rq_runtime(cfs_rq);

	check_spread(cfs_rq, prev);

	if (prev->on_rq) {
		update_stats_wait_start(cfs_rq, prev);
		/* Put 'current' back into the tree. */
		__enqueue_entity(cfs_rq, prev);
		/* in !on_rq case, update occurred at dequeue */
		update_load_avg(cfs_rq, prev, 0);
	}
	cfs_rq->curr = NULL;
}