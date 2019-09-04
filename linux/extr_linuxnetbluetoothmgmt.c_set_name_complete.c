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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mgmt_pending_cmd {int /*<<< orphan*/  sk; struct mgmt_cp_set_local_name* param; } ;
struct mgmt_cp_set_local_name {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,scalar_t__) ; 
 int /*<<< orphan*/  HCI_LE_ADV ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_LOCAL_NAME ; 
 int /*<<< orphan*/  MGMT_OP_SET_LOCAL_NAME ; 
 int /*<<< orphan*/  adv_expire (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  mgmt_cmd_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_cp_set_local_name*,int) ; 
 int /*<<< orphan*/  mgmt_cmd_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  mgmt_status (scalar_t__) ; 
 struct mgmt_pending_cmd* pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static void set_name_complete(struct hci_dev *hdev, u8 status, u16 opcode)
{
	struct mgmt_cp_set_local_name *cp;
	struct mgmt_pending_cmd *cmd;

	BT_DBG("status 0x%02x", status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_SET_LOCAL_NAME, hdev);
	if (!cmd)
		goto unlock;

	cp = cmd->param;

	if (status) {
		mgmt_cmd_status(cmd->sk, hdev->id, MGMT_OP_SET_LOCAL_NAME,
			        mgmt_status(status));
	} else {
		mgmt_cmd_complete(cmd->sk, hdev->id, MGMT_OP_SET_LOCAL_NAME, 0,
				  cp, sizeof(*cp));

		if (hci_dev_test_flag(hdev, HCI_LE_ADV))
			adv_expire(hdev, MGMT_ADV_FLAG_LOCAL_NAME);
	}

	mgmt_pending_remove(cmd);

unlock:
	hci_dev_unlock(hdev);
}