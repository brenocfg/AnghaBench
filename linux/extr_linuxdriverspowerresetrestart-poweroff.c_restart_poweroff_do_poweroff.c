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
 int /*<<< orphan*/  REBOOT_HARD ; 
 int /*<<< orphan*/  machine_restart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reboot_mode ; 

__attribute__((used)) static void restart_poweroff_do_poweroff(void)
{
	reboot_mode = REBOOT_HARD;
	machine_restart(NULL);
}