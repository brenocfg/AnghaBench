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
struct mgmt_rp_remove_advertising {scalar_t__ instance; } ;
struct mgmt_pending_cmd {int dummy; } ;
struct mgmt_cp_remove_advertising {scalar_t__ instance; } ;
struct hci_request {int /*<<< orphan*/  cmd_q; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  adv_instances; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_ADVERTISING ; 
 int /*<<< orphan*/  MGMT_OP_ADD_ADVERTISING ; 
 int /*<<< orphan*/  MGMT_OP_REMOVE_ADVERTISING ; 
 int /*<<< orphan*/  MGMT_OP_SET_LE ; 
 int /*<<< orphan*/  MGMT_STATUS_BUSY ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  __hci_req_disable_advertising (struct hci_request*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_find_adv_instance (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_req_clear_adv_instance (struct hci_dev*,struct sock*,struct hci_request*,scalar_t__,int) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_purge (struct hci_request*) ; 
 int hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_remove_advertising*,int) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 scalar_t__ pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  remove_advertising_complete ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int remove_advertising(struct sock *sk, struct hci_dev *hdev,
			      void *data, u16 data_len)
{
	struct mgmt_cp_remove_advertising *cp = data;
	struct mgmt_rp_remove_advertising rp;
	struct mgmt_pending_cmd *cmd;
	struct hci_request req;
	int err;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	if (cp->instance && !hci_find_adv_instance(hdev, cp->instance)) {
		err = mgmt_cmd_status(sk, hdev->id,
				      MGMT_OP_REMOVE_ADVERTISING,
				      MGMT_STATUS_INVALID_PARAMS);
		goto unlock;
	}

	if (pending_find(MGMT_OP_ADD_ADVERTISING, hdev) ||
	    pending_find(MGMT_OP_REMOVE_ADVERTISING, hdev) ||
	    pending_find(MGMT_OP_SET_LE, hdev)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_REMOVE_ADVERTISING,
				      MGMT_STATUS_BUSY);
		goto unlock;
	}

	if (list_empty(&hdev->adv_instances)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_REMOVE_ADVERTISING,
				      MGMT_STATUS_INVALID_PARAMS);
		goto unlock;
	}

	hci_req_init(&req, hdev);

	hci_req_clear_adv_instance(hdev, sk, &req, cp->instance, true);

	if (list_empty(&hdev->adv_instances))
		__hci_req_disable_advertising(&req);

	/* If no HCI commands have been collected so far or the HCI_ADVERTISING
	 * flag is set or the device isn't powered then we have no HCI
	 * communication to make. Simply return.
	 */
	if (skb_queue_empty(&req.cmd_q) ||
	    !hdev_is_powered(hdev) ||
	    hci_dev_test_flag(hdev, HCI_ADVERTISING)) {
		hci_req_purge(&req);
		rp.instance = cp->instance;
		err = mgmt_cmd_complete(sk, hdev->id,
					MGMT_OP_REMOVE_ADVERTISING,
					MGMT_STATUS_SUCCESS, &rp, sizeof(rp));
		goto unlock;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_REMOVE_ADVERTISING, hdev, data,
			       data_len);
	if (!cmd) {
		err = -ENOMEM;
		goto unlock;
	}

	err = hci_req_run(&req, remove_advertising_complete);
	if (err < 0)
		mgmt_pending_remove(cmd);

unlock:
	hci_dev_unlock(hdev);

	return err;
}