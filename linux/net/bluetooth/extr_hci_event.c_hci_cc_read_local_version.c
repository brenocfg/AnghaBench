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
struct hci_rp_read_local_version {int /*<<< orphan*/  lmp_subver; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  lmp_ver; int /*<<< orphan*/  hci_rev; int /*<<< orphan*/  hci_ver; scalar_t__ status; } ;
struct hci_dev {void* lmp_subver; void* manufacturer; int /*<<< orphan*/  lmp_ver; void* hci_rev; int /*<<< orphan*/  hci_ver; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_CONFIG ; 
 int /*<<< orphan*/  HCI_SETUP ; 
 void* __le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_read_local_version(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_rp_read_local_version *rp = (void *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	if (rp->status)
		return;

	if (hci_dev_test_flag(hdev, HCI_SETUP) ||
	    hci_dev_test_flag(hdev, HCI_CONFIG)) {
		hdev->hci_ver = rp->hci_ver;
		hdev->hci_rev = __le16_to_cpu(rp->hci_rev);
		hdev->lmp_ver = rp->lmp_ver;
		hdev->manufacturer = __le16_to_cpu(rp->manufacturer);
		hdev->lmp_subver = __le16_to_cpu(rp->lmp_subver);
	}
}