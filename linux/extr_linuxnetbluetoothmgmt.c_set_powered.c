#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int dummy; } ;
struct mgmt_mode {int val; } ;
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct hci_dev {TYPE_1__ power_off; int /*<<< orphan*/  req_workqueue; int /*<<< orphan*/  power_on; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENODATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_POWER_OFF_TIMEOUT ; 
 int /*<<< orphan*/  MGMT_OP_SET_POWERED ; 
 int /*<<< orphan*/  MGMT_STATUS_BUSY ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  cancel_delayed_work (TYPE_1__*) ; 
 int clean_up_hci_state (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int hdev_is_powered (struct hci_dev*) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int send_settings_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static int set_powered(struct sock *sk, struct hci_dev *hdev, void *data,
		       u16 len)
{
	struct mgmt_mode *cp = data;
	struct mgmt_pending_cmd *cmd;
	int err;

	BT_DBG("request for %s", hdev->name);

	if (cp->val != 0x00 && cp->val != 0x01)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_POWERED,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	if (pending_find(MGMT_OP_SET_POWERED, hdev)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_POWERED,
				      MGMT_STATUS_BUSY);
		goto failed;
	}

	if (!!cp->val == hdev_is_powered(hdev)) {
		err = send_settings_rsp(sk, MGMT_OP_SET_POWERED, hdev);
		goto failed;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_POWERED, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto failed;
	}

	if (cp->val) {
		queue_work(hdev->req_workqueue, &hdev->power_on);
		err = 0;
	} else {
		/* Disconnect connections, stop scans, etc */
		err = clean_up_hci_state(hdev);
		if (!err)
			queue_delayed_work(hdev->req_workqueue, &hdev->power_off,
					   HCI_POWER_OFF_TIMEOUT);

		/* ENODATA means there were no HCI commands queued */
		if (err == -ENODATA) {
			cancel_delayed_work(&hdev->power_off);
			queue_work(hdev->req_workqueue, &hdev->power_off.work);
			err = 0;
		}
	}

failed:
	hci_dev_unlock(hdev);
	return err;
}