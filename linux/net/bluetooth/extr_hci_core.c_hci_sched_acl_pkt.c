#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ priority; int /*<<< orphan*/  len; } ;
struct hci_dev {unsigned int acl_cnt; int /*<<< orphan*/  acl_last_tx; } ;
struct hci_chan {TYPE_1__* conn; int /*<<< orphan*/  sent; int /*<<< orphan*/  data_q; } ;
struct TYPE_4__ {int /*<<< orphan*/  force_active; } ;
struct TYPE_3__ {int /*<<< orphan*/  sent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_chan*,struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __check_timeout (struct hci_dev*,unsigned int) ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 struct hci_chan* hci_chan_sent (struct hci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hci_conn_enter_active_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_prio_recalculate (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_send_frame (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_sched_acl_pkt(struct hci_dev *hdev)
{
	unsigned int cnt = hdev->acl_cnt;
	struct hci_chan *chan;
	struct sk_buff *skb;
	int quote;

	__check_timeout(hdev, cnt);

	while (hdev->acl_cnt &&
	       (chan = hci_chan_sent(hdev, ACL_LINK, &quote))) {
		u32 priority = (skb_peek(&chan->data_q))->priority;
		while (quote-- && (skb = skb_peek(&chan->data_q))) {
			BT_DBG("chan %p skb %p len %d priority %u", chan, skb,
			       skb->len, skb->priority);

			/* Stop if priority has changed */
			if (skb->priority < priority)
				break;

			skb = skb_dequeue(&chan->data_q);

			hci_conn_enter_active_mode(chan->conn,
						   bt_cb(skb)->force_active);

			hci_send_frame(hdev, skb);
			hdev->acl_last_tx = jiffies;

			hdev->acl_cnt--;
			chan->sent++;
			chan->conn->sent++;
		}
	}

	if (cnt != hdev->acl_cnt)
		hci_prio_recalculate(hdev, ACL_LINK);
}