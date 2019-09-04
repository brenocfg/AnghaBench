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
struct urb {int status; TYPE_1__* dev; struct kaweth_device* context; } ;
struct sk_buff {int dummy; } ;
struct kaweth_device {TYPE_2__* net; struct sk_buff* tx_skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void kaweth_usb_transmit_complete(struct urb *urb)
{
	struct kaweth_device *kaweth = urb->context;
	struct sk_buff *skb = kaweth->tx_skb;
	int status = urb->status;

	if (unlikely(status != 0))
		if (status != -ENOENT)
			dev_dbg(&urb->dev->dev, "%s: TX status %d.\n",
				kaweth->net->name, status);

	netif_wake_queue(kaweth->net);
	dev_kfree_skb_irq(skb);
}