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
struct sk_buff {scalar_t__ len; void* pkt_type; void* protocol; struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; } ;
struct net_device {scalar_t__ type; TYPE_1__ stats; } ;
struct lowpan_peer {int dummy; } ;
struct ipv6hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_6LOWPAN ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_RX_DROP ; 
 scalar_t__ NET_RX_SUCCESS ; 
 scalar_t__ NET_SKB_PAD ; 
 void* PACKET_HOST ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 scalar_t__ give_skb_to_upper (struct sk_buff*,struct net_device*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int iphc_decompress (struct sk_buff*,struct net_device*,struct lowpan_peer*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ lowpan_is_iphc (int /*<<< orphan*/ ) ; 
 scalar_t__ lowpan_is_ipv6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static int recv_pkt(struct sk_buff *skb, struct net_device *dev,
		    struct lowpan_peer *peer)
{
	struct sk_buff *local_skb;
	int ret;

	if (!netif_running(dev))
		goto drop;

	if (dev->type != ARPHRD_6LOWPAN || !skb->len)
		goto drop;

	skb_reset_network_header(skb);

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb)
		goto drop;

	/* check that it's our buffer */
	if (lowpan_is_ipv6(*skb_network_header(skb))) {
		/* Pull off the 1-byte of 6lowpan header. */
		skb_pull(skb, 1);

		/* Copy the packet so that the IPv6 header is
		 * properly aligned.
		 */
		local_skb = skb_copy_expand(skb, NET_SKB_PAD - 1,
					    skb_tailroom(skb), GFP_ATOMIC);
		if (!local_skb)
			goto drop;

		local_skb->protocol = htons(ETH_P_IPV6);
		local_skb->pkt_type = PACKET_HOST;
		local_skb->dev = dev;

		skb_set_transport_header(local_skb, sizeof(struct ipv6hdr));

		if (give_skb_to_upper(local_skb, dev) != NET_RX_SUCCESS) {
			kfree_skb(local_skb);
			goto drop;
		}

		dev->stats.rx_bytes += skb->len;
		dev->stats.rx_packets++;

		consume_skb(local_skb);
		consume_skb(skb);
	} else if (lowpan_is_iphc(*skb_network_header(skb))) {
		local_skb = skb_clone(skb, GFP_ATOMIC);
		if (!local_skb)
			goto drop;

		local_skb->dev = dev;

		ret = iphc_decompress(local_skb, dev, peer);
		if (ret < 0) {
			BT_DBG("iphc_decompress failed: %d", ret);
			kfree_skb(local_skb);
			goto drop;
		}

		local_skb->protocol = htons(ETH_P_IPV6);
		local_skb->pkt_type = PACKET_HOST;

		if (give_skb_to_upper(local_skb, dev)
				!= NET_RX_SUCCESS) {
			kfree_skb(local_skb);
			goto drop;
		}

		dev->stats.rx_bytes += skb->len;
		dev->stats.rx_packets++;

		consume_skb(local_skb);
		consume_skb(skb);
	} else {
		BT_DBG("unknown packet type");
		goto drop;
	}

	return NET_RX_SUCCESS;

drop:
	dev->stats.rx_dropped++;
	return NET_RX_DROP;
}