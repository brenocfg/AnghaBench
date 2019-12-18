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
struct task_struct {TYPE_1__* sched_class; } ;
struct rq_flags {int dummy; } ;
struct rq {int /*<<< orphan*/  idle_balance; struct task_struct* curr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* task_tick ) (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  calc_global_load_tick (struct rq*) ; 
 struct rq* cpu_rq (int) ; 
 int /*<<< orphan*/  idle_cpu (int) ; 
 int /*<<< orphan*/  perf_event_task_tick () ; 
 int /*<<< orphan*/  psi_task_tick (struct rq*) ; 
 int /*<<< orphan*/  rq_lock (struct rq*,struct rq_flags*) ; 
 int /*<<< orphan*/  rq_unlock (struct rq*,struct rq_flags*) ; 
 int /*<<< orphan*/  sched_clock_tick () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trigger_load_balance (struct rq*) ; 
 int /*<<< orphan*/  update_rq_clock (struct rq*) ; 

void scheduler_tick(void)
{
	int cpu = smp_processor_id();
	struct rq *rq = cpu_rq(cpu);
	struct task_struct *curr = rq->curr;
	struct rq_flags rf;

	sched_clock_tick();

	rq_lock(rq, &rf);

	update_rq_clock(rq);
	curr->sched_class->task_tick(rq, curr, 0);
	calc_global_load_tick(rq);
	psi_task_tick(rq);

	rq_unlock(rq, &rf);

	perf_event_task_tick();

#ifdef CONFIG_SMP
	rq->idle_balance = idle_cpu(cpu);
	trigger_load_balance(rq);
#endif
}