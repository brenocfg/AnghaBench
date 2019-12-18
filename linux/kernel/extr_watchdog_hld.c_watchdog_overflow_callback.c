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
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ interrupts; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  hard_watchdog_warn ; 
 int /*<<< orphan*/  hardlockup_allcpu_dumped ; 
 scalar_t__ hardlockup_panic ; 
 scalar_t__ is_hardlockup () ; 
 int /*<<< orphan*/  nmi_panic (struct pt_regs*,char*) ; 
 int /*<<< orphan*/  pr_emerg (char*,int) ; 
 int /*<<< orphan*/  print_irqtrace_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_modules () ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int smp_processor_id () ; 
 scalar_t__ sysctl_hardlockup_all_cpu_backtrace ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trigger_allbutself_cpu_backtrace () ; 
 int /*<<< orphan*/  watchdog_check_timestamp () ; 
 int /*<<< orphan*/  watchdog_nmi_touch ; 

__attribute__((used)) static void watchdog_overflow_callback(struct perf_event *event,
				       struct perf_sample_data *data,
				       struct pt_regs *regs)
{
	/* Ensure the watchdog never gets throttled */
	event->hw.interrupts = 0;

	if (__this_cpu_read(watchdog_nmi_touch) == true) {
		__this_cpu_write(watchdog_nmi_touch, false);
		return;
	}

	if (!watchdog_check_timestamp())
		return;

	/* check for a hardlockup
	 * This is done by making sure our timer interrupt
	 * is incrementing.  The timer interrupt should have
	 * fired multiple times before we overflow'd.  If it hasn't
	 * then this is a good indication the cpu is stuck
	 */
	if (is_hardlockup()) {
		int this_cpu = smp_processor_id();

		/* only print hardlockups once */
		if (__this_cpu_read(hard_watchdog_warn) == true)
			return;

		pr_emerg("Watchdog detected hard LOCKUP on cpu %d\n",
			 this_cpu);
		print_modules();
		print_irqtrace_events(current);
		if (regs)
			show_regs(regs);
		else
			dump_stack();

		/*
		 * Perform all-CPU dump only once to avoid multiple hardlockups
		 * generating interleaving traces
		 */
		if (sysctl_hardlockup_all_cpu_backtrace &&
				!test_and_set_bit(0, &hardlockup_allcpu_dumped))
			trigger_allbutself_cpu_backtrace();

		if (hardlockup_panic)
			nmi_panic(regs, "Hard LOCKUP");

		__this_cpu_write(hard_watchdog_warn, true);
		return;
	}

	__this_cpu_write(hard_watchdog_warn, false);
	return;
}