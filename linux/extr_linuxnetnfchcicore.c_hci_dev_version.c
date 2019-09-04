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
struct sk_buff {int len; int* data; } ;
struct nfc_hci_dev {int sw_romlib; int sw_patch; int sw_flashlib_major; int sw_flashlib_minor; int hw_derivative; int hw_version; int hw_mpw; int hw_software; int hw_bsid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NFC_HCI_ID_MGMT_GATE ; 
 int /*<<< orphan*/  NFC_HCI_ID_MGMT_VERSION_HW ; 
 int /*<<< orphan*/  NFC_HCI_ID_MGMT_VERSION_SW ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nfc_hci_get_param (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static int hci_dev_version(struct nfc_hci_dev *hdev)
{
	int r;
	struct sk_buff *skb;

	r = nfc_hci_get_param(hdev, NFC_HCI_ID_MGMT_GATE,
			      NFC_HCI_ID_MGMT_VERSION_SW, &skb);
	if (r == -EOPNOTSUPP) {
		pr_info("Software/Hardware info not available\n");
		return 0;
	}
	if (r < 0)
		return r;

	if (skb->len != 3) {
		kfree_skb(skb);
		return -EINVAL;
	}

	hdev->sw_romlib = (skb->data[0] & 0xf0) >> 4;
	hdev->sw_patch = skb->data[0] & 0x0f;
	hdev->sw_flashlib_major = skb->data[1];
	hdev->sw_flashlib_minor = skb->data[2];

	kfree_skb(skb);

	r = nfc_hci_get_param(hdev, NFC_HCI_ID_MGMT_GATE,
			      NFC_HCI_ID_MGMT_VERSION_HW, &skb);
	if (r < 0)
		return r;

	if (skb->len != 3) {
		kfree_skb(skb);
		return -EINVAL;
	}

	hdev->hw_derivative = (skb->data[0] & 0xe0) >> 5;
	hdev->hw_version = skb->data[0] & 0x1f;
	hdev->hw_mpw = (skb->data[1] & 0xc0) >> 6;
	hdev->hw_software = skb->data[1] & 0x3f;
	hdev->hw_bsid = skb->data[2];

	kfree_skb(skb);

	pr_info("SOFTWARE INFO:\n");
	pr_info("RomLib         : %d\n", hdev->sw_romlib);
	pr_info("Patch          : %d\n", hdev->sw_patch);
	pr_info("FlashLib Major : %d\n", hdev->sw_flashlib_major);
	pr_info("FlashLib Minor : %d\n", hdev->sw_flashlib_minor);
	pr_info("HARDWARE INFO:\n");
	pr_info("Derivative     : %d\n", hdev->hw_derivative);
	pr_info("HW Version     : %d\n", hdev->hw_version);
	pr_info("#MPW           : %d\n", hdev->hw_mpw);
	pr_info("Software       : %d\n", hdev->hw_software);
	pr_info("BSID Version   : %d\n", hdev->hw_bsid);

	return 0;
}