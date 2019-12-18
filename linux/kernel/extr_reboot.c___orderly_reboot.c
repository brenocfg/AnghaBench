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
 int /*<<< orphan*/  kernel_restart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  reboot_cmd ; 
 int run_cmd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __orderly_reboot(void)
{
	int ret;

	ret = run_cmd(reboot_cmd);

	if (ret) {
		pr_warn("Failed to start orderly reboot: forcing the issue\n");
		emergency_sync();
		kernel_restart(NULL);
	}

	return ret;
}