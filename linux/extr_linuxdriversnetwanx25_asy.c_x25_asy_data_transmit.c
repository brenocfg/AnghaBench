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
struct x25_asy {int /*<<< orphan*/  lock; int /*<<< orphan*/ * tty; int /*<<< orphan*/  dev; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct x25_asy* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x25_asy_encaps (struct x25_asy*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  x25_asy_lock (struct x25_asy*) ; 

__attribute__((used)) static void x25_asy_data_transmit(struct net_device *dev, struct sk_buff *skb)
{
	struct x25_asy *sl = netdev_priv(dev);

	spin_lock(&sl->lock);
	if (netif_queue_stopped(sl->dev) || sl->tty == NULL) {
		spin_unlock(&sl->lock);
		netdev_err(dev, "tbusy drop\n");
		kfree_skb(skb);
		return;
	}
	/* We were not busy, so we are now... :-) */
	if (skb != NULL) {
		x25_asy_lock(sl);
		dev->stats.tx_bytes += skb->len;
		x25_asy_encaps(sl, skb->data, skb->len);
		dev_kfree_skb(skb);
	}
	spin_unlock(&sl->lock);
}