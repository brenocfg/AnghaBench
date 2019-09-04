#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int /*<<< orphan*/ * sched_class; } ;
struct rt_rq {int /*<<< orphan*/  rt_queued; } ;
struct rq_flags {int dummy; } ;
struct TYPE_3__ {scalar_t__ dl_nr_running; } ;
struct rq {TYPE_2__* curr; TYPE_1__ dl; scalar_t__ stop; struct rt_rq rt; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sched_class; } ;

/* Variables and functions */
 struct task_struct* RETRY_TASK ; 
 struct task_struct* _pick_next_task_rt (struct rq*) ; 
 int /*<<< orphan*/  dequeue_pushable_task (struct rq*,struct task_struct*) ; 
 scalar_t__ need_pull_rt_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  pull_rt_task (struct rq*) ; 
 int /*<<< orphan*/  put_prev_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  rq_clock_task (struct rq*) ; 
 int /*<<< orphan*/  rq_repin_lock (struct rq*,struct rq_flags*) ; 
 int /*<<< orphan*/  rq_unpin_lock (struct rq*,struct rq_flags*) ; 
 int /*<<< orphan*/  rt_queue_push_tasks (struct rq*) ; 
 int /*<<< orphan*/  rt_sched_class ; 
 scalar_t__ task_on_rq_queued (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_curr_rt (struct rq*) ; 
 int /*<<< orphan*/  update_rt_rq_load_avg (int /*<<< orphan*/ ,struct rq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct task_struct *
pick_next_task_rt(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
	struct task_struct *p;
	struct rt_rq *rt_rq = &rq->rt;

	if (need_pull_rt_task(rq, prev)) {
		/*
		 * This is OK, because current is on_cpu, which avoids it being
		 * picked for load-balance and preemption/IRQs are still
		 * disabled avoiding further scheduler activity on it and we're
		 * being very careful to re-start the picking loop.
		 */
		rq_unpin_lock(rq, rf);
		pull_rt_task(rq);
		rq_repin_lock(rq, rf);
		/*
		 * pull_rt_task() can drop (and re-acquire) rq->lock; this
		 * means a dl or stop task can slip in, in which case we need
		 * to re-start task selection.
		 */
		if (unlikely((rq->stop && task_on_rq_queued(rq->stop)) ||
			     rq->dl.dl_nr_running))
			return RETRY_TASK;
	}

	/*
	 * We may dequeue prev's rt_rq in put_prev_task().
	 * So, we update time before rt_nr_running check.
	 */
	if (prev->sched_class == &rt_sched_class)
		update_curr_rt(rq);

	if (!rt_rq->rt_queued)
		return NULL;

	put_prev_task(rq, prev);

	p = _pick_next_task_rt(rq);

	/* The running task is never eligible for pushing */
	dequeue_pushable_task(rq, p);

	rt_queue_push_tasks(rq);

	/*
	 * If prev task was rt, put_prev_task() has already updated the
	 * utilization. We only care of the case where we start to schedule a
	 * rt task
	 */
	if (rq->curr->sched_class != &rt_sched_class)
		update_rt_rq_load_avg(rq_clock_task(rq), rq, 0);

	return p;
}