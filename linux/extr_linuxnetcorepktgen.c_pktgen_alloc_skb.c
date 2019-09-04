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
struct sk_buff {struct net_device* dev; } ;
struct pktgen_dev {int cur_pkt_size; int pkt_overhead; int flags; int node; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int F_NODE ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 unsigned int LL_RESERVED_SPACE (struct net_device*) ; 
 unsigned int NET_SKB_PAD ; 
 struct sk_buff* __alloc_skb (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* __netdev_alloc_skb (struct net_device*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int numa_node_id () ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static struct sk_buff *pktgen_alloc_skb(struct net_device *dev,
					struct pktgen_dev *pkt_dev)
{
	unsigned int extralen = LL_RESERVED_SPACE(dev);
	struct sk_buff *skb = NULL;
	unsigned int size;

	size = pkt_dev->cur_pkt_size + 64 + extralen + pkt_dev->pkt_overhead;
	if (pkt_dev->flags & F_NODE) {
		int node = pkt_dev->node >= 0 ? pkt_dev->node : numa_node_id();

		skb = __alloc_skb(NET_SKB_PAD + size, GFP_NOWAIT, 0, node);
		if (likely(skb)) {
			skb_reserve(skb, NET_SKB_PAD);
			skb->dev = dev;
		}
	} else {
		 skb = __netdev_alloc_skb(dev, size, GFP_NOWAIT);
	}

	/* the caller pre-fetches from skb->data and reserves for the mac hdr */
	if (likely(skb))
		skb_reserve(skb, extralen - 16);

	return skb;
}