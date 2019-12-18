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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_mode {int val; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  mode ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_KEEP_DEBUG_KEYS ; 
 int /*<<< orphan*/  HCI_OP_WRITE_SSP_DEBUG_MODE ; 
 int /*<<< orphan*/  HCI_SSP_ENABLED ; 
 int /*<<< orphan*/  HCI_USE_DEBUG_KEYS ; 
 int /*<<< orphan*/  MGMT_OP_SET_DEBUG_KEYS ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int hci_dev_test_and_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_and_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ hdev_is_powered (struct hci_dev*) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int new_settings (struct hci_dev*,struct sock*) ; 
 int send_settings_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static int set_debug_keys(struct sock *sk, struct hci_dev *hdev,
			  void *data, u16 len)
{
	struct mgmt_mode *cp = data;
	bool changed, use_changed;
	int err;

	BT_DBG("request for %s", hdev->name);

	if (cp->val != 0x00 && cp->val != 0x01 && cp->val != 0x02)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DEBUG_KEYS,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	if (cp->val)
		changed = !hci_dev_test_and_set_flag(hdev, HCI_KEEP_DEBUG_KEYS);
	else
		changed = hci_dev_test_and_clear_flag(hdev,
						      HCI_KEEP_DEBUG_KEYS);

	if (cp->val == 0x02)
		use_changed = !hci_dev_test_and_set_flag(hdev,
							 HCI_USE_DEBUG_KEYS);
	else
		use_changed = hci_dev_test_and_clear_flag(hdev,
							  HCI_USE_DEBUG_KEYS);

	if (hdev_is_powered(hdev) && use_changed &&
	    hci_dev_test_flag(hdev, HCI_SSP_ENABLED)) {
		u8 mode = (cp->val == 0x02) ? 0x01 : 0x00;
		hci_send_cmd(hdev, HCI_OP_WRITE_SSP_DEBUG_MODE,
			     sizeof(mode), &mode);
	}

	err = send_settings_rsp(sk, MGMT_OP_SET_DEBUG_KEYS, hdev);
	if (err < 0)
		goto unlock;

	if (changed)
		err = new_settings(hdev, sk);

unlock:
	hci_dev_unlock(hdev);
	return err;
}