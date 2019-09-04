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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct hci_dev {int (* send ) (struct hci_dev*,struct sk_buff*) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  promisc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int) ; 
 int /*<<< orphan*/  hci_send_to_monitor (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_send_to_sock (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int stub1 (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_send_frame(struct hci_dev *hdev, struct sk_buff *skb)
{
	int err;

	BT_DBG("%s type %d len %d", hdev->name, hci_skb_pkt_type(skb),
	       skb->len);

	/* Time stamp */
	__net_timestamp(skb);

	/* Send copy to monitor */
	hci_send_to_monitor(hdev, skb);

	if (atomic_read(&hdev->promisc)) {
		/* Send copy to the sockets */
		hci_send_to_sock(hdev, skb);
	}

	/* Get rid of skb owner, prior to sending to the driver. */
	skb_orphan(skb);

	if (!test_bit(HCI_RUNNING, &hdev->flags)) {
		kfree_skb(skb);
		return;
	}

	err = hdev->send(hdev, skb);
	if (err < 0) {
		bt_dev_err(hdev, "sending frame failed (%d)", err);
		kfree_skb(skb);
	}
}