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
struct TYPE_2__ {int /*<<< orphan*/  rcu_cpu_has_work; int /*<<< orphan*/  rcu_cpu_kthread_status; } ;

/* Variables and functions */
 unsigned int RCU_KTHREAD_RUNNING ; 
 unsigned int RCU_KTHREAD_WAITING ; 
 unsigned int RCU_KTHREAD_YIELDING ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  rcu_core () ; 
 TYPE_1__ rcu_data ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 void* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rcu_utilization (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcu_cpu_kthread(unsigned int cpu)
{
	unsigned int *statusp = this_cpu_ptr(&rcu_data.rcu_cpu_kthread_status);
	char work, *workp = this_cpu_ptr(&rcu_data.rcu_cpu_has_work);
	int spincnt;

	for (spincnt = 0; spincnt < 10; spincnt++) {
		trace_rcu_utilization(TPS("Start CPU kthread@rcu_wait"));
		local_bh_disable();
		*statusp = RCU_KTHREAD_RUNNING;
		local_irq_disable();
		work = *workp;
		*workp = 0;
		local_irq_enable();
		if (work)
			rcu_core();
		local_bh_enable();
		if (*workp == 0) {
			trace_rcu_utilization(TPS("End CPU kthread@rcu_wait"));
			*statusp = RCU_KTHREAD_WAITING;
			return;
		}
	}
	*statusp = RCU_KTHREAD_YIELDING;
	trace_rcu_utilization(TPS("Start CPU kthread@rcu_yield"));
	schedule_timeout_interruptible(2);
	trace_rcu_utilization(TPS("End CPU kthread@rcu_yield"));
	*statusp = RCU_KTHREAD_WAITING;
}