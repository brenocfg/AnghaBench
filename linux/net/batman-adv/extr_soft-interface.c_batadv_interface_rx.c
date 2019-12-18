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
struct vlan_ethhdr {int /*<<< orphan*/  h_vlan_encapsulated_proto; } ;
struct sk_buff {int /*<<< orphan*/  mark; scalar_t__ len; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_proto; } ;
struct batadv_priv {int /*<<< orphan*/  isolation_mark; int /*<<< orphan*/  isolation_mark_mask; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_bcast_packet {scalar_t__ packet_type; } ;

/* Variables and functions */
 scalar_t__ BATADV_BCAST ; 
 int /*<<< orphan*/  BATADV_CNT_RX ; 
 int /*<<< orphan*/  BATADV_CNT_RX_BYTES ; 
 scalar_t__ ETH_HLEN ; 
#define  ETH_P_8021Q 129 
#define  ETH_P_BATMAN 128 
 scalar_t__ VLAN_ETH_HLEN ; 
 int /*<<< orphan*/  batadv_add_counter (struct batadv_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ batadv_bla_rx (struct batadv_priv*,struct sk_buff*,unsigned short,int) ; 
 unsigned short batadv_get_vid (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_inc_counter (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ batadv_is_ap_isolated (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  batadv_tt_add_temporary_global_entry (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ,unsigned short) ; 
 scalar_t__ batadv_tt_global_is_isolated (struct batadv_priv*,int /*<<< orphan*/ ,unsigned short) ; 
 scalar_t__ batadv_vlan_ap_isola_get (struct batadv_priv*,unsigned short) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,struct ethhdr*,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

void batadv_interface_rx(struct net_device *soft_iface,
			 struct sk_buff *skb, int hdr_size,
			 struct batadv_orig_node *orig_node)
{
	struct batadv_bcast_packet *batadv_bcast_packet;
	struct batadv_priv *bat_priv = netdev_priv(soft_iface);
	struct vlan_ethhdr *vhdr;
	struct ethhdr *ethhdr;
	unsigned short vid;
	bool is_bcast;

	batadv_bcast_packet = (struct batadv_bcast_packet *)skb->data;
	is_bcast = (batadv_bcast_packet->packet_type == BATADV_BCAST);

	skb_pull_rcsum(skb, hdr_size);
	skb_reset_mac_header(skb);

	/* clean the netfilter state now that the batman-adv header has been
	 * removed
	 */
	nf_reset_ct(skb);

	if (unlikely(!pskb_may_pull(skb, ETH_HLEN)))
		goto dropped;

	vid = batadv_get_vid(skb, 0);
	ethhdr = eth_hdr(skb);

	switch (ntohs(ethhdr->h_proto)) {
	case ETH_P_8021Q:
		if (!pskb_may_pull(skb, VLAN_ETH_HLEN))
			goto dropped;

		vhdr = (struct vlan_ethhdr *)skb->data;

		/* drop batman-in-batman packets to prevent loops */
		if (vhdr->h_vlan_encapsulated_proto != htons(ETH_P_BATMAN))
			break;

		/* fall through */
	case ETH_P_BATMAN:
		goto dropped;
	}

	/* skb->dev & skb->pkt_type are set here */
	skb->protocol = eth_type_trans(skb, soft_iface);
	skb_postpull_rcsum(skb, eth_hdr(skb), ETH_HLEN);

	batadv_inc_counter(bat_priv, BATADV_CNT_RX);
	batadv_add_counter(bat_priv, BATADV_CNT_RX_BYTES,
			   skb->len + ETH_HLEN);

	/* Let the bridge loop avoidance check the packet. If will
	 * not handle it, we can safely push it up.
	 */
	if (batadv_bla_rx(bat_priv, skb, vid, is_bcast))
		goto out;

	if (orig_node)
		batadv_tt_add_temporary_global_entry(bat_priv, orig_node,
						     ethhdr->h_source, vid);

	if (is_multicast_ether_addr(ethhdr->h_dest)) {
		/* set the mark on broadcast packets if AP isolation is ON and
		 * the packet is coming from an "isolated" client
		 */
		if (batadv_vlan_ap_isola_get(bat_priv, vid) &&
		    batadv_tt_global_is_isolated(bat_priv, ethhdr->h_source,
						 vid)) {
			/* save bits in skb->mark not covered by the mask and
			 * apply the mark on the rest
			 */
			skb->mark &= ~bat_priv->isolation_mark_mask;
			skb->mark |= bat_priv->isolation_mark;
		}
	} else if (batadv_is_ap_isolated(bat_priv, ethhdr->h_source,
					 ethhdr->h_dest, vid)) {
		goto dropped;
	}

	netif_rx(skb);
	goto out;

dropped:
	kfree_skb(skb);
out:
	return;
}