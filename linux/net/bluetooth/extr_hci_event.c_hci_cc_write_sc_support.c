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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct hci_dev {int /*<<< orphan*/ ** features; int /*<<< orphan*/  name; } ;
struct hci_cp_write_sc_support {scalar_t__ support; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  HCI_OP_WRITE_SC_SUPPORT ; 
 int /*<<< orphan*/  HCI_SC_ENABLED ; 
 int /*<<< orphan*/  LMP_HOST_SC ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_write_sc_support* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_write_sc_support(struct hci_dev *hdev, struct sk_buff *skb)
{
	u8 status = *((u8 *) skb->data);
	struct hci_cp_write_sc_support *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_SC_SUPPORT);
	if (!sent)
		return;

	hci_dev_lock(hdev);

	if (!status) {
		if (sent->support)
			hdev->features[1][0] |= LMP_HOST_SC;
		else
			hdev->features[1][0] &= ~LMP_HOST_SC;
	}

	if (!hci_dev_test_flag(hdev, HCI_MGMT) && !status) {
		if (sent->support)
			hci_dev_set_flag(hdev, HCI_SC_ENABLED);
		else
			hci_dev_clear_flag(hdev, HCI_SC_ENABLED);
	}

	hci_dev_unlock(hdev);
}