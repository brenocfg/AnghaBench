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
struct TYPE_5__ {scalar_t__ deadline; } ;
struct task_struct {TYPE_2__ dl; } ;
struct rq {TYPE_1__* curr; } ;
struct TYPE_6__ {scalar_t__ deadline; } ;
struct TYPE_4__ {TYPE_3__ dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_preempt_equal_dl (struct rq*,struct task_struct*) ; 
 scalar_t__ dl_entity_preempt (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  resched_curr (struct rq*) ; 
 int /*<<< orphan*/  test_tsk_need_resched (TYPE_1__*) ; 

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