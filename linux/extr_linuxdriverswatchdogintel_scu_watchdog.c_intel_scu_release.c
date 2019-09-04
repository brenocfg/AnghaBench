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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int driver_closed; int /*<<< orphan*/  timer_started; int /*<<< orphan*/  driver_open; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  intel_scu_keepalive () ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ watchdog_device ; 
 int /*<<< orphan*/  watchdog_fire () ; 

__attribute__((used)) static int intel_scu_release(struct inode *inode, struct file *file)
{
	/*
	 * This watchdog should not be closed, after the timer
	 * is started with the WDIPC_SETTIMEOUT ioctl
	 * If force_boot is set watchdog_fire() will cause an
	 * immediate reset. If force_boot is not set, the watchdog
	 * timer is refreshed for one more interval. At the end
	 * of that interval, the watchdog timer will reset the system.
	 */

	if (!test_and_clear_bit(0, &watchdog_device.driver_open)) {
		pr_debug("intel_scu_release, without open\n");
		return -ENOTTY;
	}

	if (!watchdog_device.timer_started) {
		/* Just close, since timer has not been started */
		pr_debug("closed, without starting timer\n");
		return 0;
	}

	pr_crit("Unexpected close of /dev/watchdog!\n");

	/* Since the timer was started, prevent future reopens */
	watchdog_device.driver_closed = 1;

	/* Refresh the timer for one more interval */
	intel_scu_keepalive();

	/* Reboot system (if force_boot is set) */
	watchdog_fire();

	/* We should only reach this point if force_boot is not set */
	return 0;
}