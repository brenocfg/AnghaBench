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
struct rq_flags {int dummy; } ;
struct rq {int /*<<< orphan*/  yld_count; } ;
struct TYPE_4__ {TYPE_1__* sched_class; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* yield_task ) (struct rq*) ;} ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  rq_unlock (struct rq*,struct rq_flags*) ; 
 int /*<<< orphan*/  sched_preempt_enable_no_resched () ; 
 int /*<<< orphan*/  schedstat_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  stub1 (struct rq*) ; 
 struct rq* this_rq_lock_irq (struct rq_flags*) ; 

__attribute__((used)) static void do_sched_yield(void)
{
	struct rq_flags rf;
	struct rq *rq;

	rq = this_rq_lock_irq(&rf);

	schedstat_inc(rq->yld_count);
	current->sched_class->yield_task(rq);

	/*
	 * Since we are going to call schedule() anyway, there's
	 * no need to preempt or enable interrupts:
	 */
	preempt_disable();
	rq_unlock(rq, &rf);
	sched_preempt_enable_no_resched();

	schedule();
}