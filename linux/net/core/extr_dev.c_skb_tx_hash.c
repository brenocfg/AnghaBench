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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct net_device {scalar_t__ real_num_tx_queues; TYPE_1__* tc_to_txq; scalar_t__ num_tc; } ;
struct TYPE_2__ {scalar_t__ offset; scalar_t__ count; } ;

/* Variables and functions */
 size_t netdev_get_prio_tc_map (struct net_device const*,int /*<<< orphan*/ ) ; 
 scalar_t__ reciprocal_scale (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_get_hash (struct sk_buff*) ; 
 scalar_t__ skb_get_rx_queue (struct sk_buff*) ; 
 scalar_t__ skb_rx_queue_recorded (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u16 skb_tx_hash(const struct net_device *dev,
		       const struct net_device *sb_dev,
		       struct sk_buff *skb)
{
	u32 hash;
	u16 qoffset = 0;
	u16 qcount = dev->real_num_tx_queues;

	if (dev->num_tc) {
		u8 tc = netdev_get_prio_tc_map(dev, skb->priority);

		qoffset = sb_dev->tc_to_txq[tc].offset;
		qcount = sb_dev->tc_to_txq[tc].count;
	}

	if (skb_rx_queue_recorded(skb)) {
		hash = skb_get_rx_queue(skb);
		while (unlikely(hash >= qcount))
			hash -= qcount;
		return hash + qoffset;
	}

	return (u16) reciprocal_scale(skb_get_hash(skb), qcount) + qoffset;
}