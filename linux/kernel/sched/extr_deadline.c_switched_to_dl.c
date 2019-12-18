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
struct TYPE_3__ {int /*<<< orphan*/  inactive_timer; } ;
struct task_struct {int nr_cpus_allowed; TYPE_1__ dl; } ;
struct TYPE_4__ {scalar_t__ overloaded; } ;
struct rq {struct task_struct* curr; TYPE_2__ dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_rq_bw (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  check_preempt_curr_dl (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deadline_queue_push_tasks (struct rq*) ; 
 scalar_t__ dl_task (struct task_struct*) ; 
 int hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  resched_curr (struct rq*) ; 
 int /*<<< orphan*/  task_on_rq_queued (struct task_struct*) ; 

__attribute__((used)) static void switched_to_dl(struct rq *rq, struct task_struct *p)
{
	if (hrtimer_try_to_cancel(&p->dl.inactive_timer) == 1)
		put_task_struct(p);

	/* If p is not queued we will update its parameters at next wakeup. */
	if (!task_on_rq_queued(p)) {
		add_rq_bw(&p->dl, &rq->dl);

		return;
	}

	if (rq->curr != p) {
#ifdef CONFIG_SMP
		if (p->nr_cpus_allowed > 1 && rq->dl.overloaded)
			deadline_queue_push_tasks(rq);
#endif
		if (dl_task(rq->curr))
			check_preempt_curr_dl(rq, p, 0);
		else
			resched_curr(rq);
	}
}