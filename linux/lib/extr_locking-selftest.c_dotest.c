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
struct TYPE_2__ {int softirqs_enabled; } ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int debug_locks ; 
 scalar_t__ debug_locks_verbose ; 
 int /*<<< orphan*/  expected_testcase_failures ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 unsigned long preempt_count () ; 
 int /*<<< orphan*/  preempt_count_set (unsigned long) ; 
 int /*<<< orphan*/  reset_locks () ; 
 scalar_t__ softirq_count () ; 
 int /*<<< orphan*/  testcase_successes ; 
 int /*<<< orphan*/  testcase_total ; 
 int /*<<< orphan*/  unexpected_testcase_failures ; 

__attribute__((used)) static void dotest(void (*testcase_fn)(void), int expected, int lockclass_mask)
{
	unsigned long saved_preempt_count = preempt_count();

	WARN_ON(irqs_disabled());

	testcase_fn();
	/*
	 * Filter out expected failures:
	 */
#ifndef CONFIG_PROVE_LOCKING
	if (expected == FAILURE && debug_locks) {
		expected_testcase_failures++;
		pr_cont("failed|");
	}
	else
#endif
	if (debug_locks != expected) {
		unexpected_testcase_failures++;
		pr_cont("FAILED|");
	} else {
		testcase_successes++;
		pr_cont("  ok  |");
	}
	testcase_total++;

	if (debug_locks_verbose)
		pr_cont(" lockclass mask: %x, debug_locks: %d, expected: %d\n",
			lockclass_mask, debug_locks, expected);
	/*
	 * Some tests (e.g. double-unlock) might corrupt the preemption
	 * count, so restore it:
	 */
	preempt_count_set(saved_preempt_count);
#ifdef CONFIG_TRACE_IRQFLAGS
	if (softirq_count())
		current->softirqs_enabled = 0;
	else
		current->softirqs_enabled = 1;
#endif

	reset_locks();
}