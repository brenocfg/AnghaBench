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
struct sk_buff {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  rx_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  rx_q; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int incoming; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ HCI_ACLDATA_PKT ; 
 scalar_t__ HCI_EVENT_PKT ; 
 int /*<<< orphan*/  HCI_INIT ; 
 scalar_t__ HCI_SCODATA_PKT ; 
 int /*<<< orphan*/  HCI_UP ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 scalar_t__ hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hci_recv_frame(struct hci_dev *hdev, struct sk_buff *skb)
{
	if (!hdev || (!test_bit(HCI_UP, &hdev->flags)
		      && !test_bit(HCI_INIT, &hdev->flags))) {
		kfree_skb(skb);
		return -ENXIO;
	}

	if (hci_skb_pkt_type(skb) != HCI_EVENT_PKT &&
	    hci_skb_pkt_type(skb) != HCI_ACLDATA_PKT &&
	    hci_skb_pkt_type(skb) != HCI_SCODATA_PKT) {
		kfree_skb(skb);
		return -EINVAL;
	}

	/* Incoming skb */
	bt_cb(skb)->incoming = 1;

	/* Time stamp */
	__net_timestamp(skb);

	skb_queue_tail(&hdev->rx_q, skb);
	queue_work(hdev->workqueue, &hdev->rx_work);

	return 0;
}