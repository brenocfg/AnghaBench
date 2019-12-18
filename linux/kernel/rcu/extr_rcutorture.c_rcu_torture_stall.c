#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int HZ ; 
 scalar_t__ ULONG_CMP_LT (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 unsigned long ktime_get_seconds () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  pr_alert (char*,...) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 unsigned long stall_cpu ; 
 int stall_cpu_holdoff ; 
 scalar_t__ stall_cpu_irqsoff ; 
 int /*<<< orphan*/  torture_shutdown_absorb (char*) ; 

__attribute__((used)) static int rcu_torture_stall(void *args)
{
	unsigned long stop_at;

	VERBOSE_TOROUT_STRING("rcu_torture_stall task started");
	if (stall_cpu_holdoff > 0) {
		VERBOSE_TOROUT_STRING("rcu_torture_stall begin holdoff");
		schedule_timeout_interruptible(stall_cpu_holdoff * HZ);
		VERBOSE_TOROUT_STRING("rcu_torture_stall end holdoff");
	}
	if (!kthread_should_stop()) {
		stop_at = ktime_get_seconds() + stall_cpu;
		/* RCU CPU stall is expected behavior in following code. */
		rcu_read_lock();
		if (stall_cpu_irqsoff)
			local_irq_disable();
		else
			preempt_disable();
		pr_alert("rcu_torture_stall start on CPU %d.\n",
			 smp_processor_id());
		while (ULONG_CMP_LT((unsigned long)ktime_get_seconds(),
				    stop_at))
			continue;  /* Induce RCU CPU stall warning. */
		if (stall_cpu_irqsoff)
			local_irq_enable();
		else
			preempt_enable();
		rcu_read_unlock();
		pr_alert("rcu_torture_stall end.\n");
	}
	torture_shutdown_absorb("rcu_torture_stall");
	while (!kthread_should_stop())
		schedule_timeout_interruptible(10 * HZ);
	return 0;
}