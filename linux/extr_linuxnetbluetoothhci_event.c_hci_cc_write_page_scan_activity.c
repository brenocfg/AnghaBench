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
struct sk_buff {scalar_t__ data; } ;
struct hci_dev {void* page_scan_window; void* page_scan_interval; int /*<<< orphan*/  name; } ;
struct hci_cp_write_page_scan_activity {int /*<<< orphan*/  window; int /*<<< orphan*/  interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_OP_WRITE_PAGE_SCAN_ACTIVITY ; 
 void* __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct hci_cp_write_page_scan_activity* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_write_page_scan_activity(struct hci_dev *hdev,
					    struct sk_buff *skb)
{
	u8 status = *((u8 *) skb->data);
	struct hci_cp_write_page_scan_activity *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status)
		return;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_PAGE_SCAN_ACTIVITY);
	if (!sent)
		return;

	hdev->page_scan_interval = __le16_to_cpu(sent->interval);
	hdev->page_scan_window = __le16_to_cpu(sent->window);
}