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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct hci_dev {scalar_t__ req_status; int /*<<< orphan*/  req_wait_q; int /*<<< orphan*/  req_skb; int /*<<< orphan*/  req_result; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HCI_REQ_DONE ; 
 scalar_t__ HCI_REQ_PEND ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_req_sync_complete(struct hci_dev *hdev, u8 result, u16 opcode,
				  struct sk_buff *skb)
{
	BT_DBG("%s result 0x%2.2x", hdev->name, result);

	if (hdev->req_status == HCI_REQ_PEND) {
		hdev->req_result = result;
		hdev->req_status = HCI_REQ_DONE;
		if (skb)
			hdev->req_skb = skb_get(skb);
		wake_up_interruptible(&hdev->req_wait_q);
	}
}