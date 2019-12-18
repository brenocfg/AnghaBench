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
struct task_struct {int nr_cpus_allowed; scalar_t__ prio; } ;
struct TYPE_2__ {scalar_t__ overloaded; } ;
struct rq {struct task_struct* curr; TYPE_1__ rt; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_of (struct rq*) ; 
 scalar_t__ cpu_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resched_curr (struct rq*) ; 
 int /*<<< orphan*/  rt_queue_push_tasks (struct rq*) ; 
 scalar_t__ task_on_rq_queued (struct task_struct*) ; 

__attribute__((used)) static void switched_to_rt(struct rq *rq, struct task_struct *p)
{
	/*
	 * If we are already running, then there's nothing
	 * that needs to be done. But if we are not running
	 * we may need to preempt the current running task.
	 * If that current running task is also an RT task
	 * then see if we can move to another run queue.
	 */
	if (task_on_rq_queued(p) && rq->curr != p) {
#ifdef CONFIG_SMP
		if (p->nr_cpus_allowed > 1 && rq->rt.overloaded)
			rt_queue_push_tasks(rq);
#endif /* CONFIG_SMP */
		if (p->prio < rq->curr->prio && cpu_online(cpu_of(rq)))
			resched_curr(rq);
	}
}