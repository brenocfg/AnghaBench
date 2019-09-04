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
struct sk_buff {scalar_t__ pkt_type; scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct hsr_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int NET_RX_DROP ; 
 scalar_t__ PACKET_MULTICAST ; 
 int /*<<< orphan*/  hsr_addr_subst_source (struct hsr_node*,struct sk_buff*) ; 
 int netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hsr_deliver_master(struct sk_buff *skb, struct net_device *dev,
			       struct hsr_node *node_src)
{
	bool was_multicast_frame;
	int res;

	was_multicast_frame = (skb->pkt_type == PACKET_MULTICAST);
	hsr_addr_subst_source(node_src, skb);
	skb_pull(skb, ETH_HLEN);
	res = netif_rx(skb);
	if (res == NET_RX_DROP) {
		dev->stats.rx_dropped++;
	} else {
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		if (was_multicast_frame)
			dev->stats.multicast++;
	}
}