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
typedef  int /*<<< orphan*/  u16 ;
struct vlan_pcpu_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct sk_buff {scalar_t__ pkt_type; unsigned int data; scalar_t__ len; int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  priority; int /*<<< orphan*/  mac_len; int /*<<< orphan*/  vlan_proto; struct net_device* dev; } ;
struct net_device {int flags; int /*<<< orphan*/  dev_addr; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  h_dest; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  vlan_pcpu_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_UP ; 
 scalar_t__ PACKET_HOST ; 
 scalar_t__ PACKET_MULTICAST ; 
 scalar_t__ PACKET_OTHERHOST ; 
 int VLAN_FLAG_REORDER_HDR ; 
 scalar_t__ VLAN_HLEN ; 
 int /*<<< orphan*/  __vlan_hwaccel_clear_tag (struct sk_buff*) ; 
 TYPE_2__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ ether_addr_equal_64bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_is_bridge_port (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_macvlan_port (struct net_device*) ; 
 unsigned int skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_vlan_tag_get_id (struct sk_buff*) ; 
 struct vlan_pcpu_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__* vlan_dev_priv (struct net_device*) ; 
 struct net_device* vlan_find_dev (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_get_ingress_priority (struct net_device*,int /*<<< orphan*/ ) ; 
 struct sk_buff* vlan_insert_inner_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool vlan_do_receive(struct sk_buff **skbp)
{
	struct sk_buff *skb = *skbp;
	__be16 vlan_proto = skb->vlan_proto;
	u16 vlan_id = skb_vlan_tag_get_id(skb);
	struct net_device *vlan_dev;
	struct vlan_pcpu_stats *rx_stats;

	vlan_dev = vlan_find_dev(skb->dev, vlan_proto, vlan_id);
	if (!vlan_dev)
		return false;

	skb = *skbp = skb_share_check(skb, GFP_ATOMIC);
	if (unlikely(!skb))
		return false;

	if (unlikely(!(vlan_dev->flags & IFF_UP))) {
		kfree_skb(skb);
		*skbp = NULL;
		return false;
	}

	skb->dev = vlan_dev;
	if (unlikely(skb->pkt_type == PACKET_OTHERHOST)) {
		/* Our lower layer thinks this is not local, let's make sure.
		 * This allows the VLAN to have a different MAC than the
		 * underlying device, and still route correctly. */
		if (ether_addr_equal_64bits(eth_hdr(skb)->h_dest, vlan_dev->dev_addr))
			skb->pkt_type = PACKET_HOST;
	}

	if (!(vlan_dev_priv(vlan_dev)->flags & VLAN_FLAG_REORDER_HDR) &&
	    !netif_is_macvlan_port(vlan_dev) &&
	    !netif_is_bridge_port(vlan_dev)) {
		unsigned int offset = skb->data - skb_mac_header(skb);

		/*
		 * vlan_insert_tag expect skb->data pointing to mac header.
		 * So change skb->data before calling it and change back to
		 * original position later
		 */
		skb_push(skb, offset);
		skb = *skbp = vlan_insert_inner_tag(skb, skb->vlan_proto,
						    skb->vlan_tci, skb->mac_len);
		if (!skb)
			return false;
		skb_pull(skb, offset + VLAN_HLEN);
		skb_reset_mac_len(skb);
	}

	skb->priority = vlan_get_ingress_priority(vlan_dev, skb->vlan_tci);
	__vlan_hwaccel_clear_tag(skb);

	rx_stats = this_cpu_ptr(vlan_dev_priv(vlan_dev)->vlan_pcpu_stats);

	u64_stats_update_begin(&rx_stats->syncp);
	rx_stats->rx_packets++;
	rx_stats->rx_bytes += skb->len;
	if (skb->pkt_type == PACKET_MULTICAST)
		rx_stats->rx_multicast++;
	u64_stats_update_end(&rx_stats->syncp);

	return true;
}