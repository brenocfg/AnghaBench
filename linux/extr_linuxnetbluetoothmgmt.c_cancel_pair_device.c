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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  (* cmd_complete ) (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ;struct hci_conn* user_data; } ;
struct mgmt_addr_info {int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  id; } ;
struct hci_conn {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  MGMT_OP_CANCEL_PAIR_DEVICE ; 
 int /*<<< orphan*/  MGMT_OP_PAIR_DEVICE ; 
 int /*<<< orphan*/  MGMT_STATUS_CANCELLED ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_POWERED ; 
 scalar_t__ bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_addr_info*,int) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 struct mgmt_pending_cmd* pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cancel_pair_device(struct sock *sk, struct hci_dev *hdev, void *data,
			      u16 len)
{
	struct mgmt_addr_info *addr = data;
	struct mgmt_pending_cmd *cmd;
	struct hci_conn *conn;
	int err;

	BT_DBG("");

	hci_dev_lock(hdev);

	if (!hdev_is_powered(hdev)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_CANCEL_PAIR_DEVICE,
				      MGMT_STATUS_NOT_POWERED);
		goto unlock;
	}

	cmd = pending_find(MGMT_OP_PAIR_DEVICE, hdev);
	if (!cmd) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_CANCEL_PAIR_DEVICE,
				      MGMT_STATUS_INVALID_PARAMS);
		goto unlock;
	}

	conn = cmd->user_data;

	if (bacmp(&addr->bdaddr, &conn->dst) != 0) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_CANCEL_PAIR_DEVICE,
				      MGMT_STATUS_INVALID_PARAMS);
		goto unlock;
	}

	cmd->cmd_complete(cmd, MGMT_STATUS_CANCELLED);
	mgmt_pending_remove(cmd);

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_CANCEL_PAIR_DEVICE, 0,
				addr, sizeof(*addr));
unlock:
	hci_dev_unlock(hdev);
	return err;
}