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
struct TYPE_2__ {int /*<<< orphan*/  (* wake ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pm_pr_dbg (char*) ; 
 int /*<<< orphan*/  pm_wakeup_clear (int) ; 
 scalar_t__ pm_wakeup_pending () ; 
 int /*<<< orphan*/  s2idle_enter () ; 
 TYPE_1__* s2idle_ops ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void s2idle_loop(void)
{
	pm_pr_dbg("suspend-to-idle\n");

	/*
	 * Suspend-to-idle equals:
	 * frozen processes + suspended devices + idle processors.
	 * Thus s2idle_enter() should be called right after all devices have
	 * been suspended.
	 *
	 * Wakeups during the noirq suspend of devices may be spurious, so try
	 * to avoid them upfront.
	 */
	for (;;) {
		if (s2idle_ops && s2idle_ops->wake)
			s2idle_ops->wake();

		if (pm_wakeup_pending())
			break;

		pm_wakeup_clear(false);

		s2idle_enter();
	}

	pm_pr_dbg("resume from suspend-to-idle\n");
}