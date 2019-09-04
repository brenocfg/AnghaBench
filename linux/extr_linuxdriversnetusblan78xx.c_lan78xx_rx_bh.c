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
struct urb {int dummy; } ;
struct lan78xx_net {scalar_t__ rx_qlen; scalar_t__ tx_qlen; int /*<<< orphan*/  net; int /*<<< orphan*/  txq; int /*<<< orphan*/  bh; int /*<<< orphan*/  rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOLINK ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_submit (struct lan78xx_net*,struct urb*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lan78xx_rx_bh(struct lan78xx_net *dev)
{
	struct urb *urb;
	int i;

	if (skb_queue_len(&dev->rxq) < dev->rx_qlen) {
		for (i = 0; i < 10; i++) {
			if (skb_queue_len(&dev->rxq) >= dev->rx_qlen)
				break;
			urb = usb_alloc_urb(0, GFP_ATOMIC);
			if (urb)
				if (rx_submit(dev, urb, GFP_ATOMIC) == -ENOLINK)
					return;
		}

		if (skb_queue_len(&dev->rxq) < dev->rx_qlen)
			tasklet_schedule(&dev->bh);
	}
	if (skb_queue_len(&dev->txq) < dev->tx_qlen)
		netif_wake_queue(dev->net);
}