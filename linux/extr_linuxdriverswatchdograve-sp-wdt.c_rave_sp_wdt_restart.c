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
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int RAVE_SP_RESET_DELAY_MS ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int rave_sp_wdt_restart(struct watchdog_device *wdd,
			       unsigned long action, void *data)
{
	/*
	 * The actual work was done by reboot notifier above. SP
	 * firmware waits 500 ms before issuing reset, so let's hang
	 * here for twice that delay and hopefuly we'd never reach
	 * the return statement.
	 */
	mdelay(2 * RAVE_SP_RESET_DELAY_MS);

	return -EIO;
}