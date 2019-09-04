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
struct mgmt_mode {int val; } ;
struct hci_dev {int /*<<< orphan*/  discoverable_update; int /*<<< orphan*/  req_workqueue; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_ADVERTISING ; 
 int /*<<< orphan*/  HCI_BONDABLE ; 
 int /*<<< orphan*/  HCI_DISCOVERABLE ; 
 int /*<<< orphan*/  HCI_LIMITED_PRIVACY ; 
 int /*<<< orphan*/  MGMT_OP_SET_BONDABLE ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int hci_dev_test_and_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_and_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 scalar_t__ hdev_is_powered (struct hci_dev*) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int new_settings (struct hci_dev*,struct sock*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int send_settings_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static int set_bondable(struct sock *sk, struct hci_dev *hdev, void *data,
			u16 len)
{
	struct mgmt_mode *cp = data;
	bool changed;
	int err;

	BT_DBG("request for %s", hdev->name);

	if (cp->val != 0x00 && cp->val != 0x01)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BONDABLE,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	if (cp->val)
		changed = !hci_dev_test_and_set_flag(hdev, HCI_BONDABLE);
	else
		changed = hci_dev_test_and_clear_flag(hdev, HCI_BONDABLE);

	err = send_settings_rsp(sk, MGMT_OP_SET_BONDABLE, hdev);
	if (err < 0)
		goto unlock;

	if (changed) {
		/* In limited privacy mode the change of bondable mode
		 * may affect the local advertising address.
		 */
		if (hdev_is_powered(hdev) &&
		    hci_dev_test_flag(hdev, HCI_ADVERTISING) &&
		    hci_dev_test_flag(hdev, HCI_DISCOVERABLE) &&
		    hci_dev_test_flag(hdev, HCI_LIMITED_PRIVACY))
			queue_work(hdev->req_workqueue,
				   &hdev->discoverable_update);

		err = new_settings(hdev, sk);
	}

unlock:
	hci_dev_unlock(hdev);
	return err;
}