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
struct TYPE_2__ {int /*<<< orphan*/  exec_start; } ;
struct task_struct {int on_cpu; int /*<<< orphan*/  comm; int /*<<< orphan*/ * sched_class; int /*<<< orphan*/  pi_lock; int /*<<< orphan*/  on_rq; int /*<<< orphan*/  flags; TYPE_1__ se; int /*<<< orphan*/  state; } ;
struct rq {int /*<<< orphan*/  lock; int /*<<< orphan*/  curr; struct task_struct* idle; } ;

/* Variables and functions */
 char* INIT_TASK_COMM ; 
 int /*<<< orphan*/  PF_IDLE ; 
 int /*<<< orphan*/  TASK_ON_RQ_QUEUED ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __sched_fork (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  __set_task_cpu (struct task_struct*,int) ; 
 struct rq* cpu_rq (int) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  ftrace_graph_init_idle_task (struct task_struct*,int) ; 
 int /*<<< orphan*/  idle_sched_class ; 
 int /*<<< orphan*/  init_idle_preempt_count (struct task_struct*,int) ; 
 int /*<<< orphan*/  kasan_unpoison_task_stack (struct task_struct*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sched_clock () ; 
 int /*<<< orphan*/  set_cpus_allowed_common (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  vtime_init_idle (struct task_struct*,int) ; 

void init_idle(struct task_struct *idle, int cpu)
{
	struct rq *rq = cpu_rq(cpu);
	unsigned long flags;

	raw_spin_lock_irqsave(&idle->pi_lock, flags);
	raw_spin_lock(&rq->lock);

	__sched_fork(0, idle);
	idle->state = TASK_RUNNING;
	idle->se.exec_start = sched_clock();
	idle->flags |= PF_IDLE;

	kasan_unpoison_task_stack(idle);

#ifdef CONFIG_SMP
	/*
	 * Its possible that init_idle() gets called multiple times on a task,
	 * in that case do_set_cpus_allowed() will not do the right thing.
	 *
	 * And since this is boot we can forgo the serialization.
	 */
	set_cpus_allowed_common(idle, cpumask_of(cpu));
#endif
	/*
	 * We're having a chicken and egg problem, even though we are
	 * holding rq->lock, the CPU isn't yet set to this CPU so the
	 * lockdep check in task_group() will fail.
	 *
	 * Similar case to sched_fork(). / Alternatively we could
	 * use task_rq_lock() here and obtain the other rq->lock.
	 *
	 * Silence PROVE_RCU
	 */
	rcu_read_lock();
	__set_task_cpu(idle, cpu);
	rcu_read_unlock();

	rq->idle = idle;
	rcu_assign_pointer(rq->curr, idle);
	idle->on_rq = TASK_ON_RQ_QUEUED;
#ifdef CONFIG_SMP
	idle->on_cpu = 1;
#endif
	raw_spin_unlock(&rq->lock);
	raw_spin_unlock_irqrestore(&idle->pi_lock, flags);

	/* Set the preempt count _outside_ the spinlocks! */
	init_idle_preempt_count(idle, cpu);

	/*
	 * The idle tasks have their own, simple scheduling class:
	 */
	idle->sched_class = &idle_sched_class;
	ftrace_graph_init_idle_task(idle, cpu);
	vtime_init_idle(idle, cpu);
#ifdef CONFIG_SMP
	sprintf(idle->comm, "%s/%d", INIT_TASK_COMM, cpu);
#endif
}