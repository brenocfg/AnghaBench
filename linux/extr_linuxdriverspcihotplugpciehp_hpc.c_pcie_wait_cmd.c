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
struct controller {unsigned long cmd_started; int slot_ctrl; int /*<<< orphan*/  cmd_busy; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 scalar_t__ NO_CMD_CMPL (struct controller*) ; 
 int PCI_EXP_SLTCTL_CCIE ; 
 int PCI_EXP_SLTCTL_HPIE ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 unsigned long msecs_to_jiffies (unsigned int) ; 
 int pcie_poll_cmd (struct controller*,int /*<<< orphan*/ ) ; 
 scalar_t__ pciehp_poll_mode ; 
 scalar_t__ time_before_eq (unsigned long,unsigned long) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static void pcie_wait_cmd(struct controller *ctrl)
{
	unsigned int msecs = pciehp_poll_mode ? 2500 : 1000;
	unsigned long duration = msecs_to_jiffies(msecs);
	unsigned long cmd_timeout = ctrl->cmd_started + duration;
	unsigned long now, timeout;
	int rc;

	/*
	 * If the controller does not generate notifications for command
	 * completions, we never need to wait between writes.
	 */
	if (NO_CMD_CMPL(ctrl))
		return;

	if (!ctrl->cmd_busy)
		return;

	/*
	 * Even if the command has already timed out, we want to call
	 * pcie_poll_cmd() so it can clear PCI_EXP_SLTSTA_CC.
	 */
	now = jiffies;
	if (time_before_eq(cmd_timeout, now))
		timeout = 1;
	else
		timeout = cmd_timeout - now;

	if (ctrl->slot_ctrl & PCI_EXP_SLTCTL_HPIE &&
	    ctrl->slot_ctrl & PCI_EXP_SLTCTL_CCIE)
		rc = wait_event_timeout(ctrl->queue, !ctrl->cmd_busy, timeout);
	else
		rc = pcie_poll_cmd(ctrl, jiffies_to_msecs(timeout));

	if (!rc)
		ctrl_info(ctrl, "Timeout on hotplug command %#06x (issued %u msec ago)\n",
			  ctrl->slot_ctrl,
			  jiffies_to_msecs(jiffies - ctrl->cmd_started));
}