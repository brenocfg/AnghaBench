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
struct task_struct {TYPE_1__* sched_class; int /*<<< orphan*/  recent_used_cpu; int /*<<< orphan*/  state; int /*<<< orphan*/  pi_lock; } ;
struct rq_flags {int /*<<< orphan*/  flags; } ;
struct rq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* task_woken ) (struct rq*,struct task_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENQUEUE_NOCLOCK ; 
 int /*<<< orphan*/  SD_BALANCE_FORK ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  WF_FORK ; 
 int /*<<< orphan*/  __set_task_cpu (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct rq* __task_rq_lock (struct task_struct*,struct rq_flags*) ; 
 int /*<<< orphan*/  activate_task (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_preempt_curr (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_init_entity_util_avg (struct task_struct*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_repin_lock (struct rq*,struct rq_flags*) ; 
 int /*<<< orphan*/  rq_unpin_lock (struct rq*,struct rq_flags*) ; 
 int /*<<< orphan*/  select_task_rq (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  task_cpu (struct task_struct*) ; 
 int /*<<< orphan*/  task_rq_unlock (struct rq*,struct task_struct*,struct rq_flags*) ; 
 int /*<<< orphan*/  trace_sched_wakeup_new (struct task_struct*) ; 
 int /*<<< orphan*/  update_rq_clock (struct rq*) ; 

void wake_up_new_task(struct task_struct *p)
{
	struct rq_flags rf;
	struct rq *rq;

	raw_spin_lock_irqsave(&p->pi_lock, rf.flags);
	p->state = TASK_RUNNING;
#ifdef CONFIG_SMP
	/*
	 * Fork balancing, do it here and not earlier because:
	 *  - cpus_ptr can change in the fork path
	 *  - any previously selected CPU might disappear through hotplug
	 *
	 * Use __set_task_cpu() to avoid calling sched_class::migrate_task_rq,
	 * as we're not fully set-up yet.
	 */
	p->recent_used_cpu = task_cpu(p);
	__set_task_cpu(p, select_task_rq(p, task_cpu(p), SD_BALANCE_FORK, 0));
#endif
	rq = __task_rq_lock(p, &rf);
	update_rq_clock(rq);
	post_init_entity_util_avg(p);

	activate_task(rq, p, ENQUEUE_NOCLOCK);
	trace_sched_wakeup_new(p);
	check_preempt_curr(rq, p, WF_FORK);
#ifdef CONFIG_SMP
	if (p->sched_class->task_woken) {
		/*
		 * Nothing relies on rq->lock after this, so its fine to
		 * drop it.
		 */
		rq_unpin_lock(rq, &rf);
		p->sched_class->task_woken(rq, p);
		rq_repin_lock(rq, &rf);
	}
#endif
	task_rq_unlock(rq, p, &rf);
}