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
struct mgmt_rp_get_clock_info {int which; int /*<<< orphan*/  handle; TYPE_1__ addr; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  user_data; int /*<<< orphan*/  cmd_complete; } ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_cp_get_clock_info {TYPE_2__ addr; } ;
struct hci_request {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct hci_cp_read_clock {int which; int /*<<< orphan*/  handle; TYPE_1__ addr; } ;
struct hci_conn {scalar_t__ state; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  rp ;
typedef  int /*<<< orphan*/  hci_cp ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BDADDR_ANY ; 
 scalar_t__ BDADDR_BREDR ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_OP_READ_CLOCK ; 
 int /*<<< orphan*/  MGMT_OP_GET_CLOCK_INFO ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_CONNECTED ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_POWERED ; 
 scalar_t__ bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_info_cmd_complete ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_clock_info_complete ; 
 int /*<<< orphan*/  hci_conn_get (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_conn_hold (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct mgmt_rp_get_clock_info*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 int /*<<< orphan*/  memset (struct mgmt_rp_get_clock_info*,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_get_clock_info*,int) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 

__attribute__((used)) static int get_clock_info(struct sock *sk, struct hci_dev *hdev, void *data,
			 u16 len)
{
	struct mgmt_cp_get_clock_info *cp = data;
	struct mgmt_rp_get_clock_info rp;
	struct hci_cp_read_clock hci_cp;
	struct mgmt_pending_cmd *cmd;
	struct hci_request req;
	struct hci_conn *conn;
	int err;

	BT_DBG("%s", hdev->name);

	memset(&rp, 0, sizeof(rp));
	bacpy(&rp.addr.bdaddr, &cp->addr.bdaddr);
	rp.addr.type = cp->addr.type;

	if (cp->addr.type != BDADDR_BREDR)
		return mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_CLOCK_INFO,
					 MGMT_STATUS_INVALID_PARAMS,
					 &rp, sizeof(rp));

	hci_dev_lock(hdev);

	if (!hdev_is_powered(hdev)) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_GET_CLOCK_INFO,
					MGMT_STATUS_NOT_POWERED, &rp,
					sizeof(rp));
		goto unlock;
	}

	if (bacmp(&cp->addr.bdaddr, BDADDR_ANY)) {
		conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK,
					       &cp->addr.bdaddr);
		if (!conn || conn->state != BT_CONNECTED) {
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_GET_CLOCK_INFO,
						MGMT_STATUS_NOT_CONNECTED,
						&rp, sizeof(rp));
			goto unlock;
		}
	} else {
		conn = NULL;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_GET_CLOCK_INFO, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto unlock;
	}

	cmd->cmd_complete = clock_info_cmd_complete;

	hci_req_init(&req, hdev);

	memset(&hci_cp, 0, sizeof(hci_cp));
	hci_req_add(&req, HCI_OP_READ_CLOCK, sizeof(hci_cp), &hci_cp);

	if (conn) {
		hci_conn_hold(conn);
		cmd->user_data = hci_conn_get(conn);

		hci_cp.handle = cpu_to_le16(conn->handle);
		hci_cp.which = 0x01; /* Piconet clock */
		hci_req_add(&req, HCI_OP_READ_CLOCK, sizeof(hci_cp), &hci_cp);
	}

	err = hci_req_run(&req, get_clock_info_complete);
	if (err < 0)
		mgmt_pending_remove(cmd);

unlock:
	hci_dev_unlock(hdev);
	return err;
}