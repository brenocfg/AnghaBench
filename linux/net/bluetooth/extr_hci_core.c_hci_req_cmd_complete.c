#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct hci_dev {TYPE_3__ cmd_q; struct sk_buff* sent_cmd; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ hci_req_complete_t ;
typedef  int /*<<< orphan*/  hci_req_complete_skb_t ;
struct TYPE_5__ {int req_flags; scalar_t__ req_complete; int /*<<< orphan*/  req_complete_skb; } ;
struct TYPE_6__ {TYPE_1__ hci; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CMD_PENDING ; 
 int /*<<< orphan*/  HCI_INIT ; 
 scalar_t__ HCI_OP_RESET ; 
 int HCI_REQ_SKB ; 
 int HCI_REQ_START ; 
 struct sk_buff* __skb_dequeue (TYPE_3__*) ; 
 int /*<<< orphan*/  __skb_queue_head (TYPE_3__*,struct sk_buff*) ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_is_complete (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_resend_last (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_sent_cmd_data (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hci_req_cmd_complete(struct hci_dev *hdev, u16 opcode, u8 status,
			  hci_req_complete_t *req_complete,
			  hci_req_complete_skb_t *req_complete_skb)
{
	struct sk_buff *skb;
	unsigned long flags;

	BT_DBG("opcode 0x%04x status 0x%02x", opcode, status);

	/* If the completed command doesn't match the last one that was
	 * sent we need to do special handling of it.
	 */
	if (!hci_sent_cmd_data(hdev, opcode)) {
		/* Some CSR based controllers generate a spontaneous
		 * reset complete event during init and any pending
		 * command will never be completed. In such a case we
		 * need to resend whatever was the last sent
		 * command.
		 */
		if (test_bit(HCI_INIT, &hdev->flags) && opcode == HCI_OP_RESET)
			hci_resend_last(hdev);

		return;
	}

	/* If we reach this point this event matches the last command sent */
	hci_dev_clear_flag(hdev, HCI_CMD_PENDING);

	/* If the command succeeded and there's still more commands in
	 * this request the request is not yet complete.
	 */
	if (!status && !hci_req_is_complete(hdev))
		return;

	/* If this was the last command in a request the complete
	 * callback would be found in hdev->sent_cmd instead of the
	 * command queue (hdev->cmd_q).
	 */
	if (bt_cb(hdev->sent_cmd)->hci.req_flags & HCI_REQ_SKB) {
		*req_complete_skb = bt_cb(hdev->sent_cmd)->hci.req_complete_skb;
		return;
	}

	if (bt_cb(hdev->sent_cmd)->hci.req_complete) {
		*req_complete = bt_cb(hdev->sent_cmd)->hci.req_complete;
		return;
	}

	/* Remove all pending commands belonging to this request */
	spin_lock_irqsave(&hdev->cmd_q.lock, flags);
	while ((skb = __skb_dequeue(&hdev->cmd_q))) {
		if (bt_cb(skb)->hci.req_flags & HCI_REQ_START) {
			__skb_queue_head(&hdev->cmd_q, skb);
			break;
		}

		if (bt_cb(skb)->hci.req_flags & HCI_REQ_SKB)
			*req_complete_skb = bt_cb(skb)->hci.req_complete_skb;
		else
			*req_complete = bt_cb(skb)->hci.req_complete;
		kfree_skb(skb);
	}
	spin_unlock_irqrestore(&hdev->cmd_q.lock, flags);
}