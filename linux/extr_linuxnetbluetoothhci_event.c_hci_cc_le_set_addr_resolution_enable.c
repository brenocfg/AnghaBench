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
struct hci_dev {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_LL_RPA_RESOLUTION ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_ADDR_RESOLV_ENABLE ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 scalar_t__* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_le_set_addr_resolution_enable(struct hci_dev *hdev,
						struct sk_buff *skb)
{
	__u8 *sent, status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status)
		return;

	sent = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_ADDR_RESOLV_ENABLE);
	if (!sent)
		return;

	hci_dev_lock(hdev);

	if (*sent)
		hci_dev_set_flag(hdev, HCI_LL_RPA_RESOLUTION);
	else
		hci_dev_clear_flag(hdev, HCI_LL_RPA_RESOLUTION);

	hci_dev_unlock(hdev);
}