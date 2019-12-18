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
struct hci_dev {int /*<<< orphan*/  le_resolv_list; int /*<<< orphan*/  name; } ;
struct hci_cp_le_del_from_resolv_list {int /*<<< orphan*/  bdaddr_type; int /*<<< orphan*/  bdaddr; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_OP_LE_DEL_FROM_RESOLV_LIST ; 
 int /*<<< orphan*/  hci_bdaddr_list_del_with_irk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hci_cp_le_del_from_resolv_list* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_le_del_from_resolv_list(struct hci_dev *hdev,
					  struct sk_buff *skb)
{
	struct hci_cp_le_del_from_resolv_list *sent;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status)
		return;

	sent = hci_sent_cmd_data(hdev, HCI_OP_LE_DEL_FROM_RESOLV_LIST);
	if (!sent)
		return;

	hci_bdaddr_list_del_with_irk(&hdev->le_resolv_list, &sent->bdaddr,
			    sent->bdaddr_type);
}