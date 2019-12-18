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
 int /*<<< orphan*/  CALLER_ADDR0 ; 
 unsigned int SOFTIRQ_MASK ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __preempt_count_sub (unsigned int) ; 
 int /*<<< orphan*/  get_lock_parent_ip () ; 
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 unsigned int preempt_count () ; 
 unsigned int softirq_count () ; 
 int /*<<< orphan*/  trace_preempt_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_softirqs_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __local_bh_enable(unsigned int cnt)
{
	lockdep_assert_irqs_disabled();

	if (preempt_count() == cnt)
		trace_preempt_on(CALLER_ADDR0, get_lock_parent_ip());

	if (softirq_count() == (cnt & SOFTIRQ_MASK))
		trace_softirqs_on(_RET_IP_);

	__preempt_count_sub(cnt);
}