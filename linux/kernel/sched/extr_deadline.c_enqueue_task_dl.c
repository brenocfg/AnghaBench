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
struct sched_dl_entity {scalar_t__ dl_throttled; scalar_t__ dl_boosted; } ;
struct task_struct {scalar_t__ on_rq; int nr_cpus_allowed; struct sched_dl_entity dl; int /*<<< orphan*/  normal_prio; } ;
struct rq {int /*<<< orphan*/  dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENQUEUE_REPLENISH ; 
 int ENQUEUE_RESTORE ; 
 int ENQUEUE_WAKEUP ; 
 scalar_t__ TASK_ON_RQ_MIGRATING ; 
 int /*<<< orphan*/  add_rq_bw (struct sched_dl_entity*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_running_bw (struct sched_dl_entity*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_check_constrained_dl (struct sched_dl_entity*) ; 
 int /*<<< orphan*/  dl_is_implicit (struct sched_dl_entity*) ; 
 scalar_t__ dl_prio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enqueue_dl_entity (struct sched_dl_entity*,struct sched_dl_entity*,int) ; 
 int /*<<< orphan*/  enqueue_pushable_dl_task (struct rq*,struct task_struct*) ; 
 struct task_struct* rt_mutex_get_top_task (struct task_struct*) ; 
 int /*<<< orphan*/  task_contending (struct sched_dl_entity*,int) ; 
 int /*<<< orphan*/  task_current (struct rq*,struct task_struct*) ; 

__attribute__((used)) static void enqueue_task_dl(struct rq *rq, struct task_struct *p, int flags)
{
	struct task_struct *pi_task = rt_mutex_get_top_task(p);
	struct sched_dl_entity *pi_se = &p->dl;

	/*
	 * Use the scheduling parameters of the top pi-waiter task if:
	 * - we have a top pi-waiter which is a SCHED_DEADLINE task AND
	 * - our dl_boosted is set (i.e. the pi-waiter's (absolute) deadline is
	 *   smaller than our deadline OR we are a !SCHED_DEADLINE task getting
	 *   boosted due to a SCHED_DEADLINE pi-waiter).
	 * Otherwise we keep our runtime and deadline.
	 */
	if (pi_task && dl_prio(pi_task->normal_prio) && p->dl.dl_boosted) {
		pi_se = &pi_task->dl;
	} else if (!dl_prio(p->normal_prio)) {
		/*
		 * Special case in which we have a !SCHED_DEADLINE task
		 * that is going to be deboosted, but exceeds its
		 * runtime while doing so. No point in replenishing
		 * it, as it's going to return back to its original
		 * scheduling class after this.
		 */
		BUG_ON(!p->dl.dl_boosted || flags != ENQUEUE_REPLENISH);
		return;
	}

	/*
	 * Check if a constrained deadline task was activated
	 * after the deadline but before the next period.
	 * If that is the case, the task will be throttled and
	 * the replenishment timer will be set to the next period.
	 */
	if (!p->dl.dl_throttled && !dl_is_implicit(&p->dl))
		dl_check_constrained_dl(&p->dl);

	if (p->on_rq == TASK_ON_RQ_MIGRATING || flags & ENQUEUE_RESTORE) {
		add_rq_bw(&p->dl, &rq->dl);
		add_running_bw(&p->dl, &rq->dl);
	}

	/*
	 * If p is throttled, we do not enqueue it. In fact, if it exhausted
	 * its budget it needs a replenishment and, since it now is on
	 * its rq, the bandwidth timer callback (which clearly has not
	 * run yet) will take care of this.
	 * However, the active utilization does not depend on the fact
	 * that the task is on the runqueue or not (but depends on the
	 * task's state - in GRUB parlance, "inactive" vs "active contending").
	 * In other words, even if a task is throttled its utilization must
	 * be counted in the active utilization; hence, we need to call
	 * add_running_bw().
	 */
	if (p->dl.dl_throttled && !(flags & ENQUEUE_REPLENISH)) {
		if (flags & ENQUEUE_WAKEUP)
			task_contending(&p->dl, flags);

		return;
	}

	enqueue_dl_entity(&p->dl, pi_se, flags);

	if (!task_current(rq, p) && p->nr_cpus_allowed > 1)
		enqueue_pushable_dl_task(rq, p);
}