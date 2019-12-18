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
struct sched_entity {int on_rq; int /*<<< orphan*/  vruntime; } ;
struct cfs_rq {int nr_running; scalar_t__ min_vruntime; struct sched_entity* curr; } ;

/* Variables and functions */
 int DO_ATTACH ; 
 int ENQUEUE_MIGRATED ; 
 int ENQUEUE_WAKEUP ; 
 int UPDATE_TG ; 
 int /*<<< orphan*/  __enqueue_entity (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  account_entity_enqueue (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  check_enqueue_throttle (struct cfs_rq*) ; 
 int /*<<< orphan*/  check_schedstat_required () ; 
 int /*<<< orphan*/  check_spread (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  enqueue_runnable_load_avg (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  list_add_leaf_cfs_rq (struct cfs_rq*) ; 
 int /*<<< orphan*/  place_entity (struct cfs_rq*,struct sched_entity*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cfs_group (struct sched_entity*) ; 
 int /*<<< orphan*/  update_curr (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_load_avg (struct cfs_rq*,struct sched_entity*,int) ; 
 int /*<<< orphan*/  update_stats_enqueue (struct cfs_rq*,struct sched_entity*,int) ; 

__attribute__((used)) static void
enqueue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
{
	bool renorm = !(flags & ENQUEUE_WAKEUP) || (flags & ENQUEUE_MIGRATED);
	bool curr = cfs_rq->curr == se;

	/*
	 * If we're the current task, we must renormalise before calling
	 * update_curr().
	 */
	if (renorm && curr)
		se->vruntime += cfs_rq->min_vruntime;

	update_curr(cfs_rq);

	/*
	 * Otherwise, renormalise after, such that we're placed at the current
	 * moment in time, instead of some random moment in the past. Being
	 * placed in the past could significantly boost this task to the
	 * fairness detriment of existing tasks.
	 */
	if (renorm && !curr)
		se->vruntime += cfs_rq->min_vruntime;

	/*
	 * When enqueuing a sched_entity, we must:
	 *   - Update loads to have both entity and cfs_rq synced with now.
	 *   - Add its load to cfs_rq->runnable_avg
	 *   - For group_entity, update its weight to reflect the new share of
	 *     its group cfs_rq
	 *   - Add its new weight to cfs_rq->load.weight
	 */
	update_load_avg(cfs_rq, se, UPDATE_TG | DO_ATTACH);
	update_cfs_group(se);
	enqueue_runnable_load_avg(cfs_rq, se);
	account_entity_enqueue(cfs_rq, se);

	if (flags & ENQUEUE_WAKEUP)
		place_entity(cfs_rq, se, 0);

	check_schedstat_required();
	update_stats_enqueue(cfs_rq, se, flags);
	check_spread(cfs_rq, se);
	if (!curr)
		__enqueue_entity(cfs_rq, se);
	se->on_rq = 1;

	if (cfs_rq->nr_running == 1) {
		list_add_leaf_cfs_rq(cfs_rq);
		check_enqueue_throttle(cfs_rq);
	}
}