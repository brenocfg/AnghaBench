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
struct pid_namespace {int /*<<< orphan*/  child_reaper; int /*<<< orphan*/  reboot; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LINUX_REBOOT_CMD_HALT 131 
#define  LINUX_REBOOT_CMD_POWER_OFF 130 
#define  LINUX_REBOOT_CMD_RESTART 129 
#define  LINUX_REBOOT_CMD_RESTART2 128 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 struct pid_namespace init_pid_ns ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklist_lock ; 

int reboot_pid_ns(struct pid_namespace *pid_ns, int cmd)
{
	if (pid_ns == &init_pid_ns)
		return 0;

	switch (cmd) {
	case LINUX_REBOOT_CMD_RESTART2:
	case LINUX_REBOOT_CMD_RESTART:
		pid_ns->reboot = SIGHUP;
		break;

	case LINUX_REBOOT_CMD_POWER_OFF:
	case LINUX_REBOOT_CMD_HALT:
		pid_ns->reboot = SIGINT;
		break;
	default:
		return -EINVAL;
	}

	read_lock(&tasklist_lock);
	send_sig(SIGKILL, pid_ns->child_reaper, 1);
	read_unlock(&tasklist_lock);

	do_exit(0);

	/* Not reached */
	return 0;
}