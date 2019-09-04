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
struct mgmt_pending_cmd {struct mgmt_mode* param; } ;
struct mgmt_mode {int /*<<< orphan*/  val; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_OP_SET_POWERED ; 
 struct mgmt_pending_cmd* pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 

bool mgmt_powering_down(struct hci_dev *hdev)
{
	struct mgmt_pending_cmd *cmd;
	struct mgmt_mode *cp;

	cmd = pending_find(MGMT_OP_SET_POWERED, hdev);
	if (!cmd)
		return false;

	cp = cmd->param;
	if (!cp->val)
		return true;

	return false;
}