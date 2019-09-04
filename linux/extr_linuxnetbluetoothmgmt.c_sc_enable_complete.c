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
typedef  int /*<<< orphan*/  u16 ;
struct mgmt_pending_cmd {int /*<<< orphan*/  sk; struct mgmt_mode* param; int /*<<< orphan*/  opcode; int /*<<< orphan*/  index; } ;
struct mgmt_mode {int val; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_SC_ENABLED ; 
 int /*<<< orphan*/  HCI_SC_ONLY ; 
 int /*<<< orphan*/  MGMT_OP_SET_SECURE_CONN ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  mgmt_cmd_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  mgmt_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_settings (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  send_settings_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static void sc_enable_complete(struct hci_dev *hdev, u8 status, u16 opcode)
{
	struct mgmt_pending_cmd *cmd;
	struct mgmt_mode *cp;

	BT_DBG("%s status %u", hdev->name, status);

	hci_dev_lock(hdev);

	cmd = pending_find(MGMT_OP_SET_SECURE_CONN, hdev);
	if (!cmd)
		goto unlock;

	if (status) {
		mgmt_cmd_status(cmd->sk, cmd->index, cmd->opcode,
			        mgmt_status(status));
		goto remove;
	}

	cp = cmd->param;

	switch (cp->val) {
	case 0x00:
		hci_dev_clear_flag(hdev, HCI_SC_ENABLED);
		hci_dev_clear_flag(hdev, HCI_SC_ONLY);
		break;
	case 0x01:
		hci_dev_set_flag(hdev, HCI_SC_ENABLED);
		hci_dev_clear_flag(hdev, HCI_SC_ONLY);
		break;
	case 0x02:
		hci_dev_set_flag(hdev, HCI_SC_ENABLED);
		hci_dev_set_flag(hdev, HCI_SC_ONLY);
		break;
	}

	send_settings_rsp(cmd->sk, MGMT_OP_SET_SECURE_CONN, hdev);
	new_settings(hdev, cmd->sk);

remove:
	mgmt_pending_remove(cmd);
unlock:
	hci_dev_unlock(hdev);
}