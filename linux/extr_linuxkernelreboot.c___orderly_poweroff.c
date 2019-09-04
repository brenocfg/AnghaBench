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
 int /*<<< orphan*/  emergency_sync () ; 
 int /*<<< orphan*/  kernel_power_off () ; 
 int /*<<< orphan*/  poweroff_cmd ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int run_cmd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __orderly_poweroff(bool force)
{
	int ret;

	ret = run_cmd(poweroff_cmd);

	if (ret && force) {
		pr_warn("Failed to start orderly shutdown: forcing the issue\n");

		/*
		 * I guess this should try to kick off some daemon to sync and
		 * poweroff asap.  Or not even bother syncing if we're doing an
		 * emergency shutdown?
		 */
		emergency_sync();
		kernel_power_off();
	}

	return ret;
}