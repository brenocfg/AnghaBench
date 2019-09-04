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
struct hci_dev {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  name; } ;
struct hci_chan {int /*<<< orphan*/  data_q; TYPE_1__* conn; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {struct hci_dev* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct hci_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_queue_acl (struct hci_chan*,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hci_send_acl(struct hci_chan *chan, struct sk_buff *skb, __u16 flags)
{
	struct hci_dev *hdev = chan->conn->hdev;

	BT_DBG("%s chan %p flags 0x%4.4x", hdev->name, chan, flags);

	hci_queue_acl(chan, &chan->data_q, skb, flags);

	queue_work(hdev->workqueue, &hdev->tx_work);
}