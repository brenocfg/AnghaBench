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
struct sched_entity {int depth; int /*<<< orphan*/  group_node; scalar_t__ on_rq; } ;
struct task_struct {struct sched_entity se; int /*<<< orphan*/ * sched_class; } ;
struct rq_flags {int dummy; } ;
struct cfs_rq {int /*<<< orphan*/  nr_running; struct sched_entity* curr; } ;
struct rq {int /*<<< orphan*/  cfs_tasks; struct cfs_rq cfs; } ;

/* Variables and functions */
 struct task_struct* RETRY_TASK ; 
 int /*<<< orphan*/  __maybe_unused ; 
 struct cfs_rq* cfs_rq_of (struct sched_entity*) ; 
 int /*<<< orphan*/  check_cfs_rq_runtime (struct cfs_rq*) ; 
 int /*<<< orphan*/  fair_sched_class ; 
 struct cfs_rq* group_cfs_rq (struct sched_entity*) ; 
 scalar_t__ hrtick_enabled (struct rq*) ; 
 int /*<<< orphan*/  hrtick_start_fair (struct rq*,struct task_struct*) ; 
 struct cfs_rq* is_same_group (struct sched_entity*,struct sched_entity*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int newidle_balance (struct rq*,struct rq_flags*) ; 
 struct sched_entity* parent_entity (struct sched_entity*) ; 
 struct sched_entity* pick_next_entity (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  put_prev_entity (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  put_prev_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  sched_fair_runnable (struct rq*) ; 
 int /*<<< orphan*/  set_next_entity (struct cfs_rq*,struct sched_entity*) ; 
 struct task_struct* task_of (struct sched_entity*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_curr (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_idle_rq_clock_pelt (struct rq*) ; 
 int /*<<< orphan*/  update_misfit_status (struct task_struct*,struct rq*) ; 

__attribute__((used)) static struct task_struct *
pick_next_task_fair(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
	struct cfs_rq *cfs_rq = &rq->cfs;
	struct sched_entity *se;
	struct task_struct *p;
	int new_tasks;

again:
	if (!sched_fair_runnable(rq))
		goto idle;

#ifdef CONFIG_FAIR_GROUP_SCHED
	if (!prev || prev->sched_class != &fair_sched_class)
		goto simple;

	/*
	 * Because of the set_next_buddy() in dequeue_task_fair() it is rather
	 * likely that a next task is from the same cgroup as the current.
	 *
	 * Therefore attempt to avoid putting and setting the entire cgroup
	 * hierarchy, only change the part that actually changes.
	 */

	do {
		struct sched_entity *curr = cfs_rq->curr;

		/*
		 * Since we got here without doing put_prev_entity() we also
		 * have to consider cfs_rq->curr. If it is still a runnable
		 * entity, update_curr() will update its vruntime, otherwise
		 * forget we've ever seen it.
		 */
		if (curr) {
			if (curr->on_rq)
				update_curr(cfs_rq);
			else
				curr = NULL;

			/*
			 * This call to check_cfs_rq_runtime() will do the
			 * throttle and dequeue its entity in the parent(s).
			 * Therefore the nr_running test will indeed
			 * be correct.
			 */
			if (unlikely(check_cfs_rq_runtime(cfs_rq))) {
				cfs_rq = &rq->cfs;

				if (!cfs_rq->nr_running)
					goto idle;

				goto simple;
			}
		}

		se = pick_next_entity(cfs_rq, curr);
		cfs_rq = group_cfs_rq(se);
	} while (cfs_rq);

	p = task_of(se);

	/*
	 * Since we haven't yet done put_prev_entity and if the selected task
	 * is a different task than we started out with, try and touch the
	 * least amount of cfs_rqs.
	 */
	if (prev != p) {
		struct sched_entity *pse = &prev->se;

		while (!(cfs_rq = is_same_group(se, pse))) {
			int se_depth = se->depth;
			int pse_depth = pse->depth;

			if (se_depth <= pse_depth) {
				put_prev_entity(cfs_rq_of(pse), pse);
				pse = parent_entity(pse);
			}
			if (se_depth >= pse_depth) {
				set_next_entity(cfs_rq_of(se), se);
				se = parent_entity(se);
			}
		}

		put_prev_entity(cfs_rq, pse);
		set_next_entity(cfs_rq, se);
	}

	goto done;
simple:
#endif
	if (prev)
		put_prev_task(rq, prev);

	do {
		se = pick_next_entity(cfs_rq, NULL);
		set_next_entity(cfs_rq, se);
		cfs_rq = group_cfs_rq(se);
	} while (cfs_rq);

	p = task_of(se);

done: __maybe_unused;
#ifdef CONFIG_SMP
	/*
	 * Move the next running task to the front of
	 * the list, so our cfs_tasks list becomes MRU
	 * one.
	 */
	list_move(&p->se.group_node, &rq->cfs_tasks);
#endif

	if (hrtick_enabled(rq))
		hrtick_start_fair(rq, p);

	update_misfit_status(p, rq);

	return p;

idle:
	if (!rf)
		return NULL;

	new_tasks = newidle_balance(rq, rf);

	/*
	 * Because newidle_balance() releases (and re-acquires) rq->lock, it is
	 * possible for any higher priority task to appear. In that case we
	 * must re-start the pick_next_entity() loop.
	 */
	if (new_tasks < 0)
		return RETRY_TASK;

	if (new_tasks > 0)
		goto again;

	/*
	 * rq is about to be idle, check if we need to update the
	 * lost_idle_time of clock_pelt
	 */
	update_idle_rq_clock_pelt(rq);

	return NULL;
}