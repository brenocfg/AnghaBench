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
struct TYPE_2__ {int /*<<< orphan*/  (* sync ) () ;int /*<<< orphan*/  (* wake ) () ;} ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PMSG_RESUME ; 
 int /*<<< orphan*/  PMSG_SUSPEND ; 
 int /*<<< orphan*/  dpm_noirq_begin () ; 
 int /*<<< orphan*/  dpm_noirq_end () ; 
 int /*<<< orphan*/  dpm_noirq_resume_devices (int /*<<< orphan*/ ) ; 
 int dpm_noirq_suspend_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_pr_dbg (char*) ; 
 int /*<<< orphan*/  pm_wakeup_clear (int) ; 
 scalar_t__ pm_wakeup_pending () ; 
 int /*<<< orphan*/  s2idle_enter () ; 
 TYPE_1__* s2idle_ops ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static void s2idle_loop(void)
{
	pm_pr_dbg("suspend-to-idle\n");

	for (;;) {
		int error;

		dpm_noirq_begin();

		/*
		 * Suspend-to-idle equals
		 * frozen processes + suspended devices + idle processors.
		 * Thus s2idle_enter() should be called right after
		 * all devices have been suspended.
		 *
		 * Wakeups during the noirq suspend of devices may be spurious,
		 * so prevent them from terminating the loop right away.
		 */
		error = dpm_noirq_suspend_devices(PMSG_SUSPEND);
		if (!error)
			s2idle_enter();
		else if (error == -EBUSY && pm_wakeup_pending())
			error = 0;

		if (!error && s2idle_ops && s2idle_ops->wake)
			s2idle_ops->wake();

		dpm_noirq_resume_devices(PMSG_RESUME);

		dpm_noirq_end();

		if (error)
			break;

		if (s2idle_ops && s2idle_ops->sync)
			s2idle_ops->sync();

		if (pm_wakeup_pending())
			break;

		pm_wakeup_clear(false);
	}

	pm_pr_dbg("resume from suspend-to-idle\n");
}