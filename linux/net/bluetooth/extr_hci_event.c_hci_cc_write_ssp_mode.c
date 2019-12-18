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
struct sk_buff {scalar_t__ data; } ;
struct hci_dev {int /*<<< orphan*/ ** features; int /*<<< orphan*/  name; } ;
struct hci_cp_write_ssp_mode {scalar_t__ mode; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  HCI_OP_WRITE_SSP_MODE ; 
 int /*<<< orphan*/  HCI_SSP_ENABLED ; 
 int /*<<< orphan*/  LMP_HOST_SSP ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_write_ssp_mode* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_ssp_enable_complete (struct hci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_write_ssp_mode(struct hci_dev *hdev, struct sk_buff *skb)
{
	__u8 status = *((__u8 *) skb->data);
	struct hci_cp_write_ssp_mode *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_SSP_MODE);
	if (!sent)
		return;

	hci_dev_lock(hdev);

	if (!status) {
		if (sent->mode)
			hdev->features[1][0] |= LMP_HOST_SSP;
		else
			hdev->features[1][0] &= ~LMP_HOST_SSP;
	}

	if (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_ssp_enable_complete(hdev, sent->mode, status);
	else if (!status) {
		if (sent->mode)
			hci_dev_set_flag(hdev, HCI_SSP_ENABLED);
		else
			hci_dev_clear_flag(hdev, HCI_SSP_ENABLED);
	}

	hci_dev_unlock(hdev);
}