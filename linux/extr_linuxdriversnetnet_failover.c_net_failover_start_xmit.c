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
struct sk_buff {int /*<<< orphan*/  queue_mapping; struct net_device* dev; } ;
struct net_failover_info {int /*<<< orphan*/  standby_dev; int /*<<< orphan*/  primary_dev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  slave_dev_queue_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  net_failover_drop_xmit (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  net_failover_xmit_ready (struct net_device*) ; 
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 TYPE_1__* qdisc_skb_cb (struct sk_buff*) ; 
 struct net_device* rcu_dereference_bh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t net_failover_start_xmit(struct sk_buff *skb,
					   struct net_device *dev)
{
	struct net_failover_info *nfo_info = netdev_priv(dev);
	struct net_device *xmit_dev;

	/* Try xmit via primary netdev followed by standby netdev */
	xmit_dev = rcu_dereference_bh(nfo_info->primary_dev);
	if (!xmit_dev || !net_failover_xmit_ready(xmit_dev)) {
		xmit_dev = rcu_dereference_bh(nfo_info->standby_dev);
		if (!xmit_dev || !net_failover_xmit_ready(xmit_dev))
			return net_failover_drop_xmit(skb, dev);
	}

	skb->dev = xmit_dev;
	skb->queue_mapping = qdisc_skb_cb(skb)->slave_dev_queue_mapping;

	return dev_queue_xmit(skb);
}