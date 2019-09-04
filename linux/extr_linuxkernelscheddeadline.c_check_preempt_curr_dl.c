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
struct task_struct {int /*<<< orphan*/  dl; } ;
struct rq {TYPE_1__* curr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dl; } ;

/* Variables and functions */
 scalar_t__ dl_entity_preempt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resched_curr (struct rq*) ; 

__attribute__((used)) static void check_preempt_curr_dl(struct rq *rq, struct task_struct *p,
				  int flags)
{
	if (dl_entity_preempt(&p->dl, &rq->curr->dl)) {
		resched_curr(rq);
		return;
	}

#ifdef CONFIG_SMP
	/*
	 * In the unlikely case current and p have the same deadline
	 * let us try to decide what's the best thing to do...
	 */
	if ((p->dl.deadline == rq->curr->dl.deadline) &&
	    !test_tsk_need_resched(rq->curr))
		check_preempt_equal_dl(rq, p);
#endif /* CONFIG_SMP */
}