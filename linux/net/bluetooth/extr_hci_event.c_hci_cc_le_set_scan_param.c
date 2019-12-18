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
struct hci_dev {int /*<<< orphan*/  le_scan_type; int /*<<< orphan*/  name; } ;
struct hci_cp_le_set_scan_param {int /*<<< orphan*/  type; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_SCAN_PARAM ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_le_set_scan_param* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_le_set_scan_param(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_cp_le_set_scan_param *cp;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status)
		return;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_SCAN_PARAM);
	if (!cp)
		return;

	hci_dev_lock(hdev);

	hdev->le_scan_type = cp->type;

	hci_dev_unlock(hdev);
}