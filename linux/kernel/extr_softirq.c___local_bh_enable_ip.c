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
 scalar_t__ SOFTIRQ_DISABLE_OFFSET ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_softirq () ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  in_irq () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ local_softirq_pending () ; 
 int /*<<< orphan*/  lockdep_assert_irqs_enabled () ; 
 int /*<<< orphan*/  preempt_check_resched () ; 
 int /*<<< orphan*/  preempt_count_dec () ; 
 int /*<<< orphan*/  preempt_count_sub (unsigned int) ; 
 scalar_t__ softirq_count () ; 
 int /*<<< orphan*/  trace_softirqs_on (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void __local_bh_enable_ip(unsigned long ip, unsigned int cnt)
{
	WARN_ON_ONCE(in_irq());
	lockdep_assert_irqs_enabled();
#ifdef CONFIG_TRACE_IRQFLAGS
	local_irq_disable();
#endif
	/*
	 * Are softirqs going to be turned on now:
	 */
	if (softirq_count() == SOFTIRQ_DISABLE_OFFSET)
		trace_softirqs_on(ip);
	/*
	 * Keep preemption disabled until we are done with
	 * softirq processing:
	 */
	preempt_count_sub(cnt - 1);

	if (unlikely(!in_interrupt() && local_softirq_pending())) {
		/*
		 * Run softirq if any pending. And do it in its own stack
		 * as we may be calling this deep in a task call stack already.
		 */
		do_softirq();
	}

	preempt_count_dec();
#ifdef CONFIG_TRACE_IRQFLAGS
	local_irq_enable();
#endif
	preempt_check_resched();
}