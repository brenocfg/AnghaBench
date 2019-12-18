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
typedef  void* u16 ;
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int dummy; } ;
struct mgmt_cp_set_discoverable {int val; int /*<<< orphan*/  timeout; } ;
struct hci_dev {int discov_timeout; int /*<<< orphan*/  discoverable_update; int /*<<< orphan*/  req_workqueue; int /*<<< orphan*/  discov_off; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 int /*<<< orphan*/  HCI_CONNECTABLE ; 
 int /*<<< orphan*/  HCI_DISCOVERABLE ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  HCI_LIMITED_DISCOVERABLE ; 
 int /*<<< orphan*/  MGMT_OP_SET_CONNECTABLE ; 
 int /*<<< orphan*/  MGMT_OP_SET_DISCOVERABLE ; 
 int /*<<< orphan*/  MGMT_STATUS_BUSY ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_POWERED ; 
 int /*<<< orphan*/  MGMT_STATUS_REJECTED ; 
 void* __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_change_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,void*) ; 
 int msecs_to_jiffies (int) ; 
 int new_settings (struct hci_dev*,struct sock*) ; 
 scalar_t__ pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int send_settings_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static int set_discoverable(struct sock *sk, struct hci_dev *hdev, void *data,
			    u16 len)
{
	struct mgmt_cp_set_discoverable *cp = data;
	struct mgmt_pending_cmd *cmd;
	u16 timeout;
	int err;

	BT_DBG("request for %s", hdev->name);

	if (!hci_dev_test_flag(hdev, HCI_LE_ENABLED) &&
	    !hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				       MGMT_STATUS_REJECTED);

	if (cp->val != 0x00 && cp->val != 0x01 && cp->val != 0x02)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				       MGMT_STATUS_INVALID_PARAMS);

	timeout = __le16_to_cpu(cp->timeout);

	/* Disabling discoverable requires that no timeout is set,
	 * and enabling limited discoverable requires a timeout.
	 */
	if ((cp->val == 0x00 && timeout > 0) ||
	    (cp->val == 0x02 && timeout == 0))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	if (!hdev_is_powered(hdev) && timeout > 0) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				      MGMT_STATUS_NOT_POWERED);
		goto failed;
	}

	if (pending_find(MGMT_OP_SET_DISCOVERABLE, hdev) ||
	    pending_find(MGMT_OP_SET_CONNECTABLE, hdev)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				      MGMT_STATUS_BUSY);
		goto failed;
	}

	if (!hci_dev_test_flag(hdev, HCI_CONNECTABLE)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DISCOVERABLE,
				      MGMT_STATUS_REJECTED);
		goto failed;
	}

	if (!hdev_is_powered(hdev)) {
		bool changed = false;

		/* Setting limited discoverable when powered off is
		 * not a valid operation since it requires a timeout
		 * and so no need to check HCI_LIMITED_DISCOVERABLE.
		 */
		if (!!cp->val != hci_dev_test_flag(hdev, HCI_DISCOVERABLE)) {
			hci_dev_change_flag(hdev, HCI_DISCOVERABLE);
			changed = true;
		}

		err = send_settings_rsp(sk, MGMT_OP_SET_DISCOVERABLE, hdev);
		if (err < 0)
			goto failed;

		if (changed)
			err = new_settings(hdev, sk);

		goto failed;
	}

	/* If the current mode is the same, then just update the timeout
	 * value with the new value. And if only the timeout gets updated,
	 * then no need for any HCI transactions.
	 */
	if (!!cp->val == hci_dev_test_flag(hdev, HCI_DISCOVERABLE) &&
	    (cp->val == 0x02) == hci_dev_test_flag(hdev,
						   HCI_LIMITED_DISCOVERABLE)) {
		cancel_delayed_work(&hdev->discov_off);
		hdev->discov_timeout = timeout;

		if (cp->val && hdev->discov_timeout > 0) {
			int to = msecs_to_jiffies(hdev->discov_timeout * 1000);
			queue_delayed_work(hdev->req_workqueue,
					   &hdev->discov_off, to);
		}

		err = send_settings_rsp(sk, MGMT_OP_SET_DISCOVERABLE, hdev);
		goto failed;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_DISCOVERABLE, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto failed;
	}

	/* Cancel any potential discoverable timeout that might be
	 * still active and store new timeout value. The arming of
	 * the timeout happens in the complete handler.
	 */
	cancel_delayed_work(&hdev->discov_off);
	hdev->discov_timeout = timeout;

	if (cp->val)
		hci_dev_set_flag(hdev, HCI_DISCOVERABLE);
	else
		hci_dev_clear_flag(hdev, HCI_DISCOVERABLE);

	/* Limited discoverable mode */
	if (cp->val == 0x02)
		hci_dev_set_flag(hdev, HCI_LIMITED_DISCOVERABLE);
	else
		hci_dev_clear_flag(hdev, HCI_LIMITED_DISCOVERABLE);

	queue_work(hdev->req_workqueue, &hdev->discoverable_update);
	err = 0;

failed:
	hci_dev_unlock(hdev);
	return err;
}