#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_rp_disconnect {TYPE_1__ addr; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  cmd_complete; } ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_cp_disconnect {TYPE_2__ addr; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  flags; } ;
struct hci_conn {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 scalar_t__ BDADDR_BREDR ; 
 scalar_t__ BT_CLOSED ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 scalar_t__ BT_OPEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_ERROR_REMOTE_USER_TERM ; 
 int /*<<< orphan*/  HCI_UP ; 
 int /*<<< orphan*/  MGMT_OP_DISCONNECT ; 
 int /*<<< orphan*/  MGMT_STATUS_BUSY ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_CONNECTED ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_POWERED ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdaddr_type_is_valid (scalar_t__) ; 
 int /*<<< orphan*/  generic_cmd_complete ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_conn* hci_conn_hash_lookup_le (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int hci_disconnect (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_addr_type (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct mgmt_rp_disconnect*,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_disconnect*,int) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 scalar_t__ pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int disconnect(struct sock *sk, struct hci_dev *hdev, void *data,
		      u16 len)
{
	struct mgmt_cp_disconnect *cp = data;
	struct mgmt_rp_disconnect rp;
	struct mgmt_pending_cmd *cmd;
	struct hci_conn *conn;
	int err;

	BT_DBG("");

	memset(&rp, 0, sizeof(rp));
	bacpy(&rp.addr.bdaddr, &cp->addr.bdaddr);
	rp.addr.type = cp->addr.type;

	if (!bdaddr_type_is_valid(cp->addr.type))
		return mgmt_cmd_complete(sk, hdev->id, MGMT_OP_DISCONNECT,
					 MGMT_STATUS_INVALID_PARAMS,
					 &rp, sizeof(rp));

	hci_dev_lock(hdev);

	if (!test_bit(HCI_UP, &hdev->flags)) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_DISCONNECT,
					MGMT_STATUS_NOT_POWERED, &rp,
					sizeof(rp));
		goto failed;
	}

	if (pending_find(MGMT_OP_DISCONNECT, hdev)) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_DISCONNECT,
					MGMT_STATUS_BUSY, &rp, sizeof(rp));
		goto failed;
	}

	if (cp->addr.type == BDADDR_BREDR)
		conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK,
					       &cp->addr.bdaddr);
	else
		conn = hci_conn_hash_lookup_le(hdev, &cp->addr.bdaddr,
					       le_addr_type(cp->addr.type));

	if (!conn || conn->state == BT_OPEN || conn->state == BT_CLOSED) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_DISCONNECT,
					MGMT_STATUS_NOT_CONNECTED, &rp,
					sizeof(rp));
		goto failed;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_DISCONNECT, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto failed;
	}

	cmd->cmd_complete = generic_cmd_complete;

	err = hci_disconnect(conn, HCI_ERROR_REMOTE_USER_TERM);
	if (err < 0)
		mgmt_pending_remove(cmd);

failed:
	hci_dev_unlock(hdev);
	return err;
}