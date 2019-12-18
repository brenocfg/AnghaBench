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
typedef  scalar_t__ u16 ;
struct sock {int dummy; } ;
struct mgmt_cp_set_appearance {int /*<<< orphan*/  appearance; } ;
struct hci_dev {scalar_t__ appearance; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  HCI_LE_ADV ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_APPEARANCE ; 
 int /*<<< orphan*/  MGMT_OP_SET_APPEARANCE ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  adv_expire (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext_info_changed (struct hci_dev*,struct sock*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmp_le_capable (struct hci_dev*) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_appearance(struct sock *sk, struct hci_dev *hdev, void *data,
			  u16 len)
{
	struct mgmt_cp_set_appearance *cp = data;
	u16 apperance;
	int err;

	BT_DBG("");

	if (!lmp_le_capable(hdev))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_APPEARANCE,
				       MGMT_STATUS_NOT_SUPPORTED);

	apperance = le16_to_cpu(cp->appearance);

	hci_dev_lock(hdev);

	if (hdev->appearance != apperance) {
		hdev->appearance = apperance;

		if (hci_dev_test_flag(hdev, HCI_LE_ADV))
			adv_expire(hdev, MGMT_ADV_FLAG_APPEARANCE);

		ext_info_changed(hdev, sk);
	}

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_APPEARANCE, 0, NULL,
				0);

	hci_dev_unlock(hdev);

	return err;
}