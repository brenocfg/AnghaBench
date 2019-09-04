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
struct TYPE_2__ {scalar_t__ context; } ;
struct rtl8xxxu_rx_urb {TYPE_1__ urb; int /*<<< orphan*/  list; } ;
struct rtl8xxxu_priv {int rx_urb_pending_count; int /*<<< orphan*/  rx_urb_wq; int /*<<< orphan*/  rx_urb_lock; int /*<<< orphan*/  rx_urb_pending_list; int /*<<< orphan*/  shutdown; } ;

/* Variables and functions */
 int RTL8XXXU_RX_URB_PENDING_WATER ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 

__attribute__((used)) static void rtl8xxxu_queue_rx_urb(struct rtl8xxxu_priv *priv,
				  struct rtl8xxxu_rx_urb *rx_urb)
{
	struct sk_buff *skb;
	unsigned long flags;
	int pending = 0;

	spin_lock_irqsave(&priv->rx_urb_lock, flags);

	if (!priv->shutdown) {
		list_add_tail(&rx_urb->list, &priv->rx_urb_pending_list);
		priv->rx_urb_pending_count++;
		pending = priv->rx_urb_pending_count;
	} else {
		skb = (struct sk_buff *)rx_urb->urb.context;
		dev_kfree_skb(skb);
		usb_free_urb(&rx_urb->urb);
	}

	spin_unlock_irqrestore(&priv->rx_urb_lock, flags);

	if (pending > RTL8XXXU_RX_URB_PENDING_WATER)
		schedule_work(&priv->rx_urb_wq);
}