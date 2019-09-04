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
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reboot_mode ; 
 int /*<<< orphan*/  restart_handler_list ; 

void do_kernel_restart(char *cmd)
{
	atomic_notifier_call_chain(&restart_handler_list, reboot_mode, cmd);
}