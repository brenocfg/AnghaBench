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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_mode {int val; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_HS_ENABLED ; 
 int /*<<< orphan*/  HCI_SSP_ENABLED ; 
 int /*<<< orphan*/  MGMT_OP_SET_HS ; 
 int /*<<< orphan*/  MGMT_OP_SET_SSP ; 
 scalar_t__ MGMT_STATUS_BUSY ; 
 scalar_t__ MGMT_STATUS_INVALID_PARAMS ; 
 scalar_t__ MGMT_STATUS_NOT_SUPPORTED ; 
 scalar_t__ MGMT_STATUS_REJECTED ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int hci_dev_test_and_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_and_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 scalar_t__ hdev_is_powered (struct hci_dev*) ; 
 int /*<<< orphan*/  lmp_ssp_capable (struct hci_dev*) ; 
 scalar_t__ mgmt_bredr_support (struct hci_dev*) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int new_settings (struct hci_dev*,struct sock*) ; 
 scalar_t__ pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int send_settings_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static int set_hs(struct sock *sk, struct hci_dev *hdev, void *data, u16 len)
{
	struct mgmt_mode *cp = data;
	bool changed;
	u8 status;
	int err;

	BT_DBG("request for %s", hdev->name);

	status = mgmt_bredr_support(hdev);
	if (status)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS, status);

	if (!lmp_ssp_capable(hdev))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS,
				       MGMT_STATUS_NOT_SUPPORTED);

	if (!hci_dev_test_flag(hdev, HCI_SSP_ENABLED))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS,
				       MGMT_STATUS_REJECTED);

	if (cp->val != 0x00 && cp->val != 0x01)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	if (pending_find(MGMT_OP_SET_SSP, hdev)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS,
				      MGMT_STATUS_BUSY);
		goto unlock;
	}

	if (cp->val) {
		changed = !hci_dev_test_and_set_flag(hdev, HCI_HS_ENABLED);
	} else {
		if (hdev_is_powered(hdev)) {
			err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_HS,
					      MGMT_STATUS_REJECTED);
			goto unlock;
		}

		changed = hci_dev_test_and_clear_flag(hdev, HCI_HS_ENABLED);
	}

	err = send_settings_rsp(sk, MGMT_OP_SET_HS, hdev);
	if (err < 0)
		goto unlock;

	if (changed)
		err = new_settings(hdev, sk);

unlock:
	hci_dev_unlock(hdev);
	return err;
}