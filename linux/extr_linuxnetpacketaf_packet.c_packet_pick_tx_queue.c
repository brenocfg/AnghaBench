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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {struct net_device* dev; } ;
struct net_device_ops {int /*<<< orphan*/  (* ndo_select_queue ) (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *)) ;} ;
struct net_device {struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  __packet_pick_tx_queue (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_cap_txqueue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *)) ; 

__attribute__((used)) static u16 packet_pick_tx_queue(struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;
	const struct net_device_ops *ops = dev->netdev_ops;
	u16 queue_index;

	if (ops->ndo_select_queue) {
		queue_index = ops->ndo_select_queue(dev, skb, NULL,
						    __packet_pick_tx_queue);
		queue_index = netdev_cap_txqueue(dev, queue_index);
	} else {
		queue_index = __packet_pick_tx_queue(dev, skb, NULL);
	}

	return queue_index;
}