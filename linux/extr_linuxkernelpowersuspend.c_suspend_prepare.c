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
typedef  int /*<<< orphan*/  suspend_state_t ;
struct TYPE_2__ {int /*<<< orphan*/  failed_freeze; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  PM_POST_SUSPEND ; 
 int /*<<< orphan*/  PM_SUSPEND_PREPARE ; 
 int /*<<< orphan*/  SUSPEND_FREEZE ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int __pm_notifier_call_chain (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  dpm_save_failed_step (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_prepare_console () ; 
 int /*<<< orphan*/  pm_restore_console () ; 
 int /*<<< orphan*/  sleep_state_supported (int /*<<< orphan*/ ) ; 
 int suspend_freeze_processes () ; 
 TYPE_1__ suspend_stats ; 
 int /*<<< orphan*/  trace_suspend_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int suspend_prepare(suspend_state_t state)
{
	int error, nr_calls = 0;

	if (!sleep_state_supported(state))
		return -EPERM;

	pm_prepare_console();

	error = __pm_notifier_call_chain(PM_SUSPEND_PREPARE, -1, &nr_calls);
	if (error) {
		nr_calls--;
		goto Finish;
	}

	trace_suspend_resume(TPS("freeze_processes"), 0, true);
	error = suspend_freeze_processes();
	trace_suspend_resume(TPS("freeze_processes"), 0, false);
	if (!error)
		return 0;

	suspend_stats.failed_freeze++;
	dpm_save_failed_step(SUSPEND_FREEZE);
 Finish:
	__pm_notifier_call_chain(PM_POST_SUSPEND, nr_calls, NULL);
	pm_restore_console();
	return error;
}