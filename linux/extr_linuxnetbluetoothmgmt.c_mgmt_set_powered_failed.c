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
typedef  int /*<<< orphan*/  u8 ;
struct mgmt_pending_cmd {int /*<<< orphan*/  sk; } ;
struct hci_dev {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ERFKILL ; 
 int /*<<< orphan*/  MGMT_OP_SET_POWERED ; 
 int /*<<< orphan*/  MGMT_STATUS_FAILED ; 
 int /*<<< orphan*/  MGMT_STATUS_RFKILLED ; 
 int /*<<< orphan*/  mgmt_cmd_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 struct mgmt_pending_cmd* pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 

void mgmt_set_powered_failed(struct hci_dev *hdev, int err)
{
	struct mgmt_pending_cmd *cmd;
	u8 status;

	cmd = pending_find(MGMT_OP_SET_POWERED, hdev);
	if (!cmd)
		return;

	if (err == -ERFKILL)
		status = MGMT_STATUS_RFKILLED;
	else
		status = MGMT_STATUS_FAILED;

	mgmt_cmd_status(cmd->sk, hdev->id, MGMT_OP_SET_POWERED, status);

	mgmt_pending_remove(cmd);
}