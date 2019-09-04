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
struct TYPE_3__ {int /*<<< orphan*/  exec_start; } ;
struct task_struct {TYPE_1__ se; int /*<<< orphan*/ * sched_class; } ;
struct sched_dl_entity {int dummy; } ;
struct rq_flags {int dummy; } ;
struct dl_rq {int /*<<< orphan*/  dl_nr_running; } ;
struct rq {TYPE_2__* curr; scalar_t__ stop; struct dl_rq dl; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sched_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct task_struct* RETRY_TASK ; 
 int /*<<< orphan*/  deadline_queue_push_tasks (struct rq*) ; 
 int /*<<< orphan*/  dequeue_pushable_dl_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  dl_sched_class ; 
 struct task_struct* dl_task_of (struct sched_dl_entity*) ; 
 scalar_t__ hrtick_enabled (struct rq*) ; 
 scalar_t__ need_pull_dl_task (struct rq*,struct task_struct*) ; 
 struct sched_dl_entity* pick_next_dl_entity (struct rq*,struct dl_rq*) ; 
 int /*<<< orphan*/  pull_dl_task (struct rq*) ; 
 int /*<<< orphan*/  put_prev_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  rq_clock_task (struct rq*) ; 
 int /*<<< orphan*/  rq_repin_lock (struct rq*,struct rq_flags*) ; 
 int /*<<< orphan*/  rq_unpin_lock (struct rq*,struct rq_flags*) ; 
 int /*<<< orphan*/  start_hrtick_dl (struct rq*,struct task_struct*) ; 
 scalar_t__ task_on_rq_queued (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_curr_dl (struct rq*) ; 
 int /*<<< orphan*/  update_dl_rq_load_avg (int /*<<< orphan*/ ,struct rq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct task_struct *
pick_next_task_dl(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
	struct sched_dl_entity *dl_se;
	struct task_struct *p;
	struct dl_rq *dl_rq;

	dl_rq = &rq->dl;

	if (need_pull_dl_task(rq, prev)) {
		/*
		 * This is OK, because current is on_cpu, which avoids it being
		 * picked for load-balance and preemption/IRQs are still
		 * disabled avoiding further scheduler activity on it and we're
		 * being very careful to re-start the picking loop.
		 */
		rq_unpin_lock(rq, rf);
		pull_dl_task(rq);
		rq_repin_lock(rq, rf);
		/*
		 * pull_dl_task() can drop (and re-acquire) rq->lock; this
		 * means a stop task can slip in, in which case we need to
		 * re-start task selection.
		 */
		if (rq->stop && task_on_rq_queued(rq->stop))
			return RETRY_TASK;
	}

	/*
	 * When prev is DL, we may throttle it in put_prev_task().
	 * So, we update time before we check for dl_nr_running.
	 */
	if (prev->sched_class == &dl_sched_class)
		update_curr_dl(rq);

	if (unlikely(!dl_rq->dl_nr_running))
		return NULL;

	put_prev_task(rq, prev);

	dl_se = pick_next_dl_entity(rq, dl_rq);
	BUG_ON(!dl_se);

	p = dl_task_of(dl_se);
	p->se.exec_start = rq_clock_task(rq);

	/* Running task will never be pushed. */
       dequeue_pushable_dl_task(rq, p);

	if (hrtick_enabled(rq))
		start_hrtick_dl(rq, p);

	deadline_queue_push_tasks(rq);

	if (rq->curr->sched_class != &dl_sched_class)
		update_dl_rq_load_avg(rq_clock_task(rq), rq, 0);

	return p;
}