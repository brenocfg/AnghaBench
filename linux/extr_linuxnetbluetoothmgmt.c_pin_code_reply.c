#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  cmd_complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdaddr; } ;
struct mgmt_cp_pin_code_reply {int pin_len; TYPE_1__* pin_code; TYPE_1__ addr; } ;
struct mgmt_cp_pin_code_neg_reply {int /*<<< orphan*/  addr; } ;
struct hci_dev {int /*<<< orphan*/  id; } ;
struct hci_cp_pin_code_reply {int pin_len; int /*<<< orphan*/ * pin_code; int /*<<< orphan*/  bdaddr; } ;
struct hci_conn {scalar_t__ pending_sec_level; } ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 scalar_t__ BT_SECURITY_HIGH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_OP_PIN_CODE_REPLY ; 
 int /*<<< orphan*/  MGMT_OP_PIN_CODE_REPLY ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_CONNECTED ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_POWERED ; 
 int /*<<< orphan*/  addr_cmd_complete ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_pin_code_reply*) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int send_pin_code_neg_reply (struct sock*,struct hci_dev*,struct mgmt_cp_pin_code_neg_reply*) ; 

__attribute__((used)) static int pin_code_reply(struct sock *sk, struct hci_dev *hdev, void *data,
			  u16 len)
{
	struct hci_conn *conn;
	struct mgmt_cp_pin_code_reply *cp = data;
	struct hci_cp_pin_code_reply reply;
	struct mgmt_pending_cmd *cmd;
	int err;

	BT_DBG("");

	hci_dev_lock(hdev);

	if (!hdev_is_powered(hdev)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_PIN_CODE_REPLY,
				      MGMT_STATUS_NOT_POWERED);
		goto failed;
	}

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &cp->addr.bdaddr);
	if (!conn) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_PIN_CODE_REPLY,
				      MGMT_STATUS_NOT_CONNECTED);
		goto failed;
	}

	if (conn->pending_sec_level == BT_SECURITY_HIGH && cp->pin_len != 16) {
		struct mgmt_cp_pin_code_neg_reply ncp;

		memcpy(&ncp.addr, &cp->addr, sizeof(ncp.addr));

		bt_dev_err(hdev, "PIN code is not 16 bytes long");

		err = send_pin_code_neg_reply(sk, hdev, &ncp);
		if (err >= 0)
			err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_PIN_CODE_REPLY,
					      MGMT_STATUS_INVALID_PARAMS);

		goto failed;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_PIN_CODE_REPLY, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto failed;
	}

	cmd->cmd_complete = addr_cmd_complete;

	bacpy(&reply.bdaddr, &cp->addr.bdaddr);
	reply.pin_len = cp->pin_len;
	memcpy(reply.pin_code, cp->pin_code, sizeof(reply.pin_code));

	err = hci_send_cmd(hdev, HCI_OP_PIN_CODE_REPLY, sizeof(reply), &reply);
	if (err < 0)
		mgmt_pending_remove(cmd);

failed:
	hci_dev_unlock(hdev);
	return err;
}