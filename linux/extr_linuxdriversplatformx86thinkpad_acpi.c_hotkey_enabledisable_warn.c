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
 scalar_t__ TPACPI_LIFE_RUNNING ; 
 int /*<<< orphan*/  WARN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_fmt (char*) ; 
 scalar_t__ tpacpi_lifecycle ; 
 int /*<<< orphan*/  tpacpi_log_usertask (char*) ; 

__attribute__((used)) static void hotkey_enabledisable_warn(bool enable)
{
	tpacpi_log_usertask("procfs hotkey enable/disable");
	if (!WARN((tpacpi_lifecycle == TPACPI_LIFE_RUNNING || !enable),
		  pr_fmt("hotkey enable/disable functionality has been removed from the driver.  Hotkeys are always enabled.\n")))
		pr_err("Please remove the hotkey=enable module parameter, it is deprecated.  Hotkeys are always enabled.\n");
}