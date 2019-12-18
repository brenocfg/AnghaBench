#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int /*<<< orphan*/  pushable_dl_tasks; int /*<<< orphan*/  pushable_tasks; scalar_t__ on_cpu; int /*<<< orphan*/  sched_info; int /*<<< orphan*/  pi_lock; TYPE_1__* sched_class; int /*<<< orphan*/  se; int /*<<< orphan*/  prio; scalar_t__ sched_reset_on_fork; int /*<<< orphan*/  normal_prio; void* static_prio; scalar_t__ rt_priority; int /*<<< orphan*/  policy; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int /*<<< orphan*/  normal_prio; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* task_fork ) (struct task_struct*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  MAX_PRIO ; 
 void* NICE_TO_PRIO (int /*<<< orphan*/ ) ; 
 scalar_t__ PRIO_TO_NICE (void*) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCHED_NORMAL ; 
 int /*<<< orphan*/  TASK_NEW ; 
 int /*<<< orphan*/  __normal_prio (struct task_struct*) ; 
 int /*<<< orphan*/  __sched_fork (unsigned long,struct task_struct*) ; 
 int /*<<< orphan*/  __set_task_cpu (struct task_struct*,int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 scalar_t__ dl_prio (int /*<<< orphan*/ ) ; 
 TYPE_1__ fair_sched_class ; 
 int /*<<< orphan*/  init_entity_runnable_average (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_task_preempt_count (struct task_struct*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plist_node_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ rt_prio (int /*<<< orphan*/ ) ; 
 TYPE_1__ rt_sched_class ; 
 int /*<<< orphan*/  sched_info_on () ; 
 int /*<<< orphan*/  set_load_weight (struct task_struct*,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (struct task_struct*) ; 
 scalar_t__ task_has_dl_policy (struct task_struct*) ; 
 scalar_t__ task_has_rt_policy (struct task_struct*) ; 
 int /*<<< orphan*/  uclamp_fork (struct task_struct*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

int sched_fork(unsigned long clone_flags, struct task_struct *p)
{
	unsigned long flags;

	__sched_fork(clone_flags, p);
	/*
	 * We mark the process as NEW here. This guarantees that
	 * nobody will actually run it, and a signal or other external
	 * event cannot wake it up and insert it on the runqueue either.
	 */
	p->state = TASK_NEW;

	/*
	 * Make sure we do not leak PI boosting priority to the child.
	 */
	p->prio = current->normal_prio;

	uclamp_fork(p);

	/*
	 * Revert to default priority/policy on fork if requested.
	 */
	if (unlikely(p->sched_reset_on_fork)) {
		if (task_has_dl_policy(p) || task_has_rt_policy(p)) {
			p->policy = SCHED_NORMAL;
			p->static_prio = NICE_TO_PRIO(0);
			p->rt_priority = 0;
		} else if (PRIO_TO_NICE(p->static_prio) < 0)
			p->static_prio = NICE_TO_PRIO(0);

		p->prio = p->normal_prio = __normal_prio(p);
		set_load_weight(p, false);

		/*
		 * We don't need the reset flag anymore after the fork. It has
		 * fulfilled its duty:
		 */
		p->sched_reset_on_fork = 0;
	}

	if (dl_prio(p->prio))
		return -EAGAIN;
	else if (rt_prio(p->prio))
		p->sched_class = &rt_sched_class;
	else
		p->sched_class = &fair_sched_class;

	init_entity_runnable_average(&p->se);

	/*
	 * The child is not yet in the pid-hash so no cgroup attach races,
	 * and the cgroup is pinned to this child due to cgroup_fork()
	 * is ran before sched_fork().
	 *
	 * Silence PROVE_RCU.
	 */
	raw_spin_lock_irqsave(&p->pi_lock, flags);
	/*
	 * We're setting the CPU for the first time, we don't migrate,
	 * so use __set_task_cpu().
	 */
	__set_task_cpu(p, smp_processor_id());
	if (p->sched_class->task_fork)
		p->sched_class->task_fork(p);
	raw_spin_unlock_irqrestore(&p->pi_lock, flags);

#ifdef CONFIG_SCHED_INFO
	if (likely(sched_info_on()))
		memset(&p->sched_info, 0, sizeof(p->sched_info));
#endif
#if defined(CONFIG_SMP)
	p->on_cpu = 0;
#endif
	init_task_preempt_count(p);
#ifdef CONFIG_SMP
	plist_node_init(&p->pushable_tasks, MAX_PRIO);
	RB_CLEAR_NODE(&p->pushable_dl_tasks);
#endif
	return 0;
}