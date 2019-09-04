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
struct sk_buff {scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_fifo_errors; } ;
struct net_device {TYPE_2__ stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  ch_id; } ;
struct net_dev_context {scalar_t__ is_mamac; TYPE_1__ tx; int /*<<< orphan*/  iface; } ;
struct mbo {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  comp ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct mbo* most_get_mbo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  most_put_mbo (struct mbo*) ; 
 int /*<<< orphan*/  most_submit_mbo (struct mbo*) ; 
 struct net_dev_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int skb_to_mamac (struct sk_buff*,struct mbo*) ; 
 int skb_to_mep (struct sk_buff*,struct mbo*) ; 

__attribute__((used)) static netdev_tx_t most_nd_start_xmit(struct sk_buff *skb,
				      struct net_device *dev)
{
	struct net_dev_context *nd = netdev_priv(dev);
	struct mbo *mbo;
	int ret;

	mbo = most_get_mbo(nd->iface, nd->tx.ch_id, &comp);

	if (!mbo) {
		netif_stop_queue(dev);
		dev->stats.tx_fifo_errors++;
		return NETDEV_TX_BUSY;
	}

	if (nd->is_mamac)
		ret = skb_to_mamac(skb, mbo);
	else
		ret = skb_to_mep(skb, mbo);

	if (ret) {
		most_put_mbo(mbo);
		dev->stats.tx_dropped++;
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	most_submit_mbo(mbo);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
	kfree_skb(skb);
	return NETDEV_TX_OK;
}