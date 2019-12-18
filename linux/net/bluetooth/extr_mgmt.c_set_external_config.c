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
struct mgmt_cp_set_external_config {int config; } ;
struct hci_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  power_on; int /*<<< orphan*/  req_workqueue; int /*<<< orphan*/  id; int /*<<< orphan*/  quirks; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_AUTO_OFF ; 
 int /*<<< orphan*/  HCI_CONFIG ; 
 int /*<<< orphan*/  HCI_EXT_CONFIGURED ; 
 int /*<<< orphan*/  HCI_QUIRK_EXTERNAL_CONFIG ; 
 int /*<<< orphan*/  HCI_RAW ; 
 int /*<<< orphan*/  HCI_UNCONFIGURED ; 
 int /*<<< orphan*/  MGMT_OP_SET_EXTERNAL_CONFIG ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  MGMT_STATUS_REJECTED ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_and_change_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int hci_dev_test_and_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_and_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 scalar_t__ hdev_is_powered (struct hci_dev*) ; 
 scalar_t__ is_configured (struct hci_dev*) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_index_added (struct hci_dev*) ; 
 int /*<<< orphan*/  mgmt_index_removed (struct hci_dev*) ; 
 int new_options (struct hci_dev*,struct sock*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int send_options_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_external_config(struct sock *sk, struct hci_dev *hdev,
			       void *data, u16 len)
{
	struct mgmt_cp_set_external_config *cp = data;
	bool changed;
	int err;

	BT_DBG("%s", hdev->name);

	if (hdev_is_powered(hdev))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_EXTERNAL_CONFIG,
				       MGMT_STATUS_REJECTED);

	if (cp->config != 0x00 && cp->config != 0x01)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_EXTERNAL_CONFIG,
				         MGMT_STATUS_INVALID_PARAMS);

	if (!test_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_EXTERNAL_CONFIG,
				       MGMT_STATUS_NOT_SUPPORTED);

	hci_dev_lock(hdev);

	if (cp->config)
		changed = !hci_dev_test_and_set_flag(hdev, HCI_EXT_CONFIGURED);
	else
		changed = hci_dev_test_and_clear_flag(hdev, HCI_EXT_CONFIGURED);

	err = send_options_rsp(sk, MGMT_OP_SET_EXTERNAL_CONFIG, hdev);
	if (err < 0)
		goto unlock;

	if (!changed)
		goto unlock;

	err = new_options(hdev, sk);

	if (hci_dev_test_flag(hdev, HCI_UNCONFIGURED) == is_configured(hdev)) {
		mgmt_index_removed(hdev);

		if (hci_dev_test_and_change_flag(hdev, HCI_UNCONFIGURED)) {
			hci_dev_set_flag(hdev, HCI_CONFIG);
			hci_dev_set_flag(hdev, HCI_AUTO_OFF);

			queue_work(hdev->req_workqueue, &hdev->power_on);
		} else {
			set_bit(HCI_RAW, &hdev->flags);
			mgmt_index_added(hdev);
		}
	}

unlock:
	hci_dev_unlock(hdev);
	return err;
}