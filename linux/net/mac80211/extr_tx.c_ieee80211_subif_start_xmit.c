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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  __ieee80211_subif_start_xmit (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  ieee80211_convert_to_unicast (struct sk_buff*,struct net_device*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  ieee80211_multicast_to_unicast (struct sk_buff*,struct net_device*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

netdev_tx_t ieee80211_subif_start_xmit(struct sk_buff *skb,
				       struct net_device *dev)
{
	if (unlikely(ieee80211_multicast_to_unicast(skb, dev))) {
		struct sk_buff_head queue;

		__skb_queue_head_init(&queue);
		ieee80211_convert_to_unicast(skb, dev, &queue);
		while ((skb = __skb_dequeue(&queue)))
			__ieee80211_subif_start_xmit(skb, dev, 0, 0);
	} else {
		__ieee80211_subif_start_xmit(skb, dev, 0, 0);
	}

	return NETDEV_TX_OK;
}