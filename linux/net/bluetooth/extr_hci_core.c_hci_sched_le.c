#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ priority; int /*<<< orphan*/  len; } ;
struct hci_dev {int le_cnt; int acl_cnt; scalar_t__ le_pkts; scalar_t__ le_last_tx; int /*<<< orphan*/  name; } ;
struct hci_chan {TYPE_1__* conn; int /*<<< orphan*/  sent; int /*<<< orphan*/  data_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  sent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_chan*,...) ; 
 int /*<<< orphan*/  HCI_UNCONFIGURED ; 
 int HZ ; 
 int /*<<< orphan*/  LE_LINK ; 
 struct hci_chan* hci_chan_sent (struct hci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hci_conn_num (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_link_tx_to (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_prio_recalculate (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_send_frame (struct hci_dev*,struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void hci_sched_le(struct hci_dev *hdev)
{
	struct hci_chan *chan;
	struct sk_buff *skb;
	int quote, cnt, tmp;

	BT_DBG("%s", hdev->name);

	if (!hci_conn_num(hdev, LE_LINK))
		return;

	if (!hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) {
		/* LE tx timeout must be longer than maximum
		 * link supervision timeout (40.9 seconds) */
		if (!hdev->le_cnt && hdev->le_pkts &&
		    time_after(jiffies, hdev->le_last_tx + HZ * 45))
			hci_link_tx_to(hdev, LE_LINK);
	}

	cnt = hdev->le_pkts ? hdev->le_cnt : hdev->acl_cnt;
	tmp = cnt;
	while (cnt && (chan = hci_chan_sent(hdev, LE_LINK, &quote))) {
		u32 priority = (skb_peek(&chan->data_q))->priority;
		while (quote-- && (skb = skb_peek(&chan->data_q))) {
			BT_DBG("chan %p skb %p len %d priority %u", chan, skb,
			       skb->len, skb->priority);

			/* Stop if priority has changed */
			if (skb->priority < priority)
				break;

			skb = skb_dequeue(&chan->data_q);

			hci_send_frame(hdev, skb);
			hdev->le_last_tx = jiffies;

			cnt--;
			chan->sent++;
			chan->conn->sent++;
		}
	}

	if (hdev->le_pkts)
		hdev->le_cnt = cnt;
	else
		hdev->acl_cnt = cnt;

	if (cnt != tmp)
		hci_prio_recalculate(hdev, LE_LINK);
}