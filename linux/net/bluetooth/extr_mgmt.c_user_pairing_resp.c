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
struct mgmt_pending_cmd {int /*<<< orphan*/  cmd_complete; } ;
struct hci_cp_user_passkey_reply {int /*<<< orphan*/  passkey; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_addr_info {scalar_t__ type; struct hci_cp_user_passkey_reply bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  id; } ;
struct hci_conn {int dummy; } ;
typedef  int /*<<< orphan*/  cp ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 scalar_t__ BDADDR_BREDR ; 
 scalar_t__ BDADDR_LE_PUBLIC ; 
 scalar_t__ BDADDR_LE_RANDOM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_OP_USER_PASSKEY_REPLY ; 
 int /*<<< orphan*/  MGMT_STATUS_FAILED ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_CONNECTED ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_POWERED ; 
 int /*<<< orphan*/  MGMT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  addr_cmd_complete ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,struct hci_cp_user_passkey_reply*) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,struct hci_cp_user_passkey_reply*) ; 
 struct hci_conn* hci_conn_hash_lookup_le (struct hci_dev*,struct hci_cp_user_passkey_reply*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_user_passkey_reply*) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 int /*<<< orphan*/  le_addr_type (scalar_t__) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_addr_info*,int) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_addr_info*,int) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int smp_user_confirm_reply (struct hci_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int user_pairing_resp(struct sock *sk, struct hci_dev *hdev,
			     struct mgmt_addr_info *addr, u16 mgmt_op,
			     u16 hci_op, __le32 passkey)
{
	struct mgmt_pending_cmd *cmd;
	struct hci_conn *conn;
	int err;

	hci_dev_lock(hdev);

	if (!hdev_is_powered(hdev)) {
		err = mgmt_cmd_complete(sk, hdev->id, mgmt_op,
					MGMT_STATUS_NOT_POWERED, addr,
					sizeof(*addr));
		goto done;
	}

	if (addr->type == BDADDR_BREDR)
		conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &addr->bdaddr);
	else
		conn = hci_conn_hash_lookup_le(hdev, &addr->bdaddr,
					       le_addr_type(addr->type));

	if (!conn) {
		err = mgmt_cmd_complete(sk, hdev->id, mgmt_op,
					MGMT_STATUS_NOT_CONNECTED, addr,
					sizeof(*addr));
		goto done;
	}

	if (addr->type == BDADDR_LE_PUBLIC || addr->type == BDADDR_LE_RANDOM) {
		err = smp_user_confirm_reply(conn, mgmt_op, passkey);
		if (!err)
			err = mgmt_cmd_complete(sk, hdev->id, mgmt_op,
						MGMT_STATUS_SUCCESS, addr,
						sizeof(*addr));
		else
			err = mgmt_cmd_complete(sk, hdev->id, mgmt_op,
						MGMT_STATUS_FAILED, addr,
						sizeof(*addr));

		goto done;
	}

	cmd = mgmt_pending_add(sk, mgmt_op, hdev, addr, sizeof(*addr));
	if (!cmd) {
		err = -ENOMEM;
		goto done;
	}

	cmd->cmd_complete = addr_cmd_complete;

	/* Continue with pairing via HCI */
	if (hci_op == HCI_OP_USER_PASSKEY_REPLY) {
		struct hci_cp_user_passkey_reply cp;

		bacpy(&cp.bdaddr, &addr->bdaddr);
		cp.passkey = passkey;
		err = hci_send_cmd(hdev, hci_op, sizeof(cp), &cp);
	} else
		err = hci_send_cmd(hdev, hci_op, sizeof(addr->bdaddr),
				   &addr->bdaddr);

	if (err < 0)
		mgmt_pending_remove(cmd);

done:
	hci_dev_unlock(hdev);
	return err;
}