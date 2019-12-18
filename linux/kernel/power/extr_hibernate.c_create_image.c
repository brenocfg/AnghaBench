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
 int /*<<< orphan*/  PMSG_FREEZE ; 
 int /*<<< orphan*/  PMSG_RECOVER ; 
 int /*<<< orphan*/  PMSG_RESTORE ; 
 int /*<<< orphan*/  PMSG_THAW ; 
 int /*<<< orphan*/  PM_EVENT_HIBERNATE ; 
 int /*<<< orphan*/  SYSTEM_RUNNING ; 
 int /*<<< orphan*/  SYSTEM_SUSPEND ; 
 int /*<<< orphan*/  TEST_CORE ; 
 int /*<<< orphan*/  TEST_CPUS ; 
 int /*<<< orphan*/  TEST_PLATFORM ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int arch_resume_nosmt () ; 
 int /*<<< orphan*/  clear_free_pages () ; 
 int /*<<< orphan*/  dpm_resume_start (int /*<<< orphan*/ ) ; 
 int dpm_suspend_end (int /*<<< orphan*/ ) ; 
 int events_check_enabled ; 
 scalar_t__ hibernation_test (int /*<<< orphan*/ ) ; 
 int in_suspend ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  platform_finish (int) ; 
 int /*<<< orphan*/  platform_leave (int) ; 
 int platform_pre_snapshot (int) ; 
 scalar_t__ pm_wakeup_pending () ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  restore_processor_state () ; 
 int /*<<< orphan*/  save_processor_state () ; 
 int suspend_disable_secondary_cpus () ; 
 int /*<<< orphan*/  suspend_enable_secondary_cpus () ; 
 int swsusp_arch_suspend () ; 
 int /*<<< orphan*/  syscore_resume () ; 
 int syscore_suspend () ; 
 int /*<<< orphan*/  system_state ; 
 int /*<<< orphan*/  trace_suspend_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int create_image(int platform_mode)
{
	int error;

	error = dpm_suspend_end(PMSG_FREEZE);
	if (error) {
		pr_err("Some devices failed to power down, aborting hibernation\n");
		return error;
	}

	error = platform_pre_snapshot(platform_mode);
	if (error || hibernation_test(TEST_PLATFORM))
		goto Platform_finish;

	error = suspend_disable_secondary_cpus();
	if (error || hibernation_test(TEST_CPUS))
		goto Enable_cpus;

	local_irq_disable();

	system_state = SYSTEM_SUSPEND;

	error = syscore_suspend();
	if (error) {
		pr_err("Some system devices failed to power down, aborting hibernation\n");
		goto Enable_irqs;
	}

	if (hibernation_test(TEST_CORE) || pm_wakeup_pending())
		goto Power_up;

	in_suspend = 1;
	save_processor_state();
	trace_suspend_resume(TPS("machine_suspend"), PM_EVENT_HIBERNATE, true);
	error = swsusp_arch_suspend();
	/* Restore control flow magically appears here */
	restore_processor_state();
	trace_suspend_resume(TPS("machine_suspend"), PM_EVENT_HIBERNATE, false);
	if (error)
		pr_err("Error %d creating hibernation image\n", error);

	if (!in_suspend) {
		events_check_enabled = false;
		clear_free_pages();
	}

	platform_leave(platform_mode);

 Power_up:
	syscore_resume();

 Enable_irqs:
	system_state = SYSTEM_RUNNING;
	local_irq_enable();

 Enable_cpus:
	suspend_enable_secondary_cpus();

	/* Allow architectures to do nosmt-specific post-resume dances */
	if (!in_suspend)
		error = arch_resume_nosmt();

 Platform_finish:
	platform_finish(platform_mode);

	dpm_resume_start(in_suspend ?
		(error ? PMSG_RECOVER : PMSG_THAW) : PMSG_RESTORE);

	return error;
}