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
struct hci_cp_le_set_ext_scan_params {scalar_t__ data; } ;
struct hci_cp_le_scan_phy_params {int /*<<< orphan*/  type; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_EXT_SCAN_PARAMS ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_le_set_ext_scan_params* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_le_set_ext_scan_param(struct hci_dev *hdev,
					 struct sk_buff *skb)
{
	struct hci_cp_le_set_ext_scan_params *cp;
	__u8 status = *((__u8 *) skb->data);
	struct hci_cp_le_scan_phy_params *phy_param;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status)
		return;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_EXT_SCAN_PARAMS);
	if (!cp)
		return;

	phy_param = (void *)cp->data;

	hci_dev_lock(hdev);

	hdev->le_scan_type = phy_param->type;

	hci_dev_unlock(hdev);
}