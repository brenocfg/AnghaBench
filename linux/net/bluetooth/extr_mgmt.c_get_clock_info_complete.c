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
struct mgmt_pending_cmd {int /*<<< orphan*/  (* cmd_complete ) (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ;} ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_read_clock {int /*<<< orphan*/  handle; scalar_t__ which; } ;
struct hci_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_OP_READ_CLOCK ; 
 int /*<<< orphan*/  MGMT_OP_GET_CLOCK_INFO ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_read_clock* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  mgmt_status (int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* pending_find_data (int /*<<< orphan*/ ,struct hci_dev*,struct hci_conn*) ; 
 int /*<<< orphan*/  stub1 (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_clock_info_complete(struct hci_dev *hdev, u8 status, u16 opcode)
{
	struct hci_cp_read_clock *hci_cp;
	struct mgmt_pending_cmd *cmd;
	struct hci_conn *conn;

	BT_DBG("%s status %u", hdev->name, status);

	hci_dev_lock(hdev);

	hci_cp = hci_sent_cmd_data(hdev, HCI_OP_READ_CLOCK);
	if (!hci_cp)
		goto unlock;

	if (hci_cp->which) {
		u16 handle = __le16_to_cpu(hci_cp->handle);
		conn = hci_conn_hash_lookup_handle(hdev, handle);
	} else {
		conn = NULL;
	}

	cmd = pending_find_data(MGMT_OP_GET_CLOCK_INFO, hdev, conn);
	if (!cmd)
		goto unlock;

	cmd->cmd_complete(cmd, mgmt_status(status));
	mgmt_pending_remove(cmd);

unlock:
	hci_dev_unlock(hdev);
}