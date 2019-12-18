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
struct sock {int dummy; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CONNECTABLE ; 
 int /*<<< orphan*/  HCI_DISCOVERABLE ; 
 int /*<<< orphan*/  MGMT_OP_SET_CONNECTABLE ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_update_scan (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_update_background_scan (struct hci_dev*) ; 
 int new_settings (struct hci_dev*,struct sock*) ; 
 int send_settings_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static int set_connectable_update_settings(struct hci_dev *hdev,
					   struct sock *sk, u8 val)
{
	bool changed = false;
	int err;

	if (!!val != hci_dev_test_flag(hdev, HCI_CONNECTABLE))
		changed = true;

	if (val) {
		hci_dev_set_flag(hdev, HCI_CONNECTABLE);
	} else {
		hci_dev_clear_flag(hdev, HCI_CONNECTABLE);
		hci_dev_clear_flag(hdev, HCI_DISCOVERABLE);
	}

	err = send_settings_rsp(sk, MGMT_OP_SET_CONNECTABLE, hdev);
	if (err < 0)
		return err;

	if (changed) {
		hci_req_update_scan(hdev);
		hci_update_background_scan(hdev);
		return new_settings(hdev, sk);
	}

	return 0;
}