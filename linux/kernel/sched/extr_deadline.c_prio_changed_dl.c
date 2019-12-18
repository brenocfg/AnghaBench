#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  deadline; } ;
struct task_struct {TYPE_3__ dl; } ;
struct TYPE_4__ {int /*<<< orphan*/  curr; } ;
struct TYPE_5__ {TYPE_1__ earliest_dl; int /*<<< orphan*/  overloaded; } ;
struct rq {TYPE_2__ dl; struct task_struct* curr; } ;

/* Variables and functions */
 int /*<<< orphan*/  deadline_queue_pull_task (struct rq*) ; 
 scalar_t__ dl_time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resched_curr (struct rq*) ; 
 scalar_t__ task_on_rq_queued (struct task_struct*) ; 

__attribute__((used)) static void prio_changed_dl(struct rq *rq, struct task_struct *p,
			    int oldprio)
{
	if (task_on_rq_queued(p) || rq->curr == p) {
#ifdef CONFIG_SMP
		/*
		 * This might be too much, but unfortunately
		 * we don't have the old deadline value, and
		 * we can't argue if the task is increasing
		 * or lowering its prio, so...
		 */
		if (!rq->dl.overloaded)
			deadline_queue_pull_task(rq);

		/*
		 * If we now have a earlier deadline task than p,
		 * then reschedule, provided p is still on this
		 * runqueue.
		 */
		if (dl_time_before(rq->dl.earliest_dl.curr, p->dl.deadline))
			resched_curr(rq);
#else
		/*
		 * Again, we don't know if p has a earlier
		 * or later deadline, so let's blindly set a
		 * (maybe not needed) rescheduling point.
		 */
		resched_curr(rq);
#endif /* CONFIG_SMP */
	}
}