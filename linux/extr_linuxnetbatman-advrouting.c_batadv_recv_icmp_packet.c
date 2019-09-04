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
struct sk_buff {int len; scalar_t__ data; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_icmp_packet_rr {size_t rr_cur; int /*<<< orphan*/ * rr; } ;
struct batadv_icmp_header {scalar_t__ msg_type; int ttl; int /*<<< orphan*/  dst; } ;
struct batadv_hard_iface {int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 scalar_t__ BATADV_ECHO_REPLY ; 
 scalar_t__ BATADV_ECHO_REQUEST ; 
 size_t BATADV_RR_LEN ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int NET_XMIT_SUCCESS ; 
 scalar_t__ batadv_is_my_mac (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 struct batadv_orig_node* batadv_orig_hash_find (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 int batadv_recv_icmp_ttl_exceeded (struct batadv_priv*,struct sk_buff*) ; 
 int batadv_recv_my_icmp_packet (struct batadv_priv*,struct sk_buff*) ; 
 int batadv_send_skb_to_orig (struct sk_buff*,struct batadv_orig_node*,struct batadv_hard_iface*) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_cow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int batadv_recv_icmp_packet(struct sk_buff *skb,
			    struct batadv_hard_iface *recv_if)
{
	struct batadv_priv *bat_priv = netdev_priv(recv_if->soft_iface);
	struct batadv_icmp_header *icmph;
	struct batadv_icmp_packet_rr *icmp_packet_rr;
	struct ethhdr *ethhdr;
	struct batadv_orig_node *orig_node = NULL;
	int hdr_size = sizeof(struct batadv_icmp_header);
	int res, ret = NET_RX_DROP;

	/* drop packet if it has not necessary minimum size */
	if (unlikely(!pskb_may_pull(skb, hdr_size)))
		goto free_skb;

	ethhdr = eth_hdr(skb);

	/* packet with unicast indication but non-unicast recipient */
	if (!is_valid_ether_addr(ethhdr->h_dest))
		goto free_skb;

	/* packet with broadcast/multicast sender address */
	if (is_multicast_ether_addr(ethhdr->h_source))
		goto free_skb;

	/* not for me */
	if (!batadv_is_my_mac(bat_priv, ethhdr->h_dest))
		goto free_skb;

	icmph = (struct batadv_icmp_header *)skb->data;

	/* add record route information if not full */
	if ((icmph->msg_type == BATADV_ECHO_REPLY ||
	     icmph->msg_type == BATADV_ECHO_REQUEST) &&
	    skb->len >= sizeof(struct batadv_icmp_packet_rr)) {
		if (skb_linearize(skb) < 0)
			goto free_skb;

		/* create a copy of the skb, if needed, to modify it. */
		if (skb_cow(skb, ETH_HLEN) < 0)
			goto free_skb;

		ethhdr = eth_hdr(skb);
		icmph = (struct batadv_icmp_header *)skb->data;
		icmp_packet_rr = (struct batadv_icmp_packet_rr *)icmph;
		if (icmp_packet_rr->rr_cur >= BATADV_RR_LEN)
			goto free_skb;

		ether_addr_copy(icmp_packet_rr->rr[icmp_packet_rr->rr_cur],
				ethhdr->h_dest);
		icmp_packet_rr->rr_cur++;
	}

	/* packet for me */
	if (batadv_is_my_mac(bat_priv, icmph->dst))
		return batadv_recv_my_icmp_packet(bat_priv, skb);

	/* TTL exceeded */
	if (icmph->ttl < 2)
		return batadv_recv_icmp_ttl_exceeded(bat_priv, skb);

	/* get routing information */
	orig_node = batadv_orig_hash_find(bat_priv, icmph->dst);
	if (!orig_node)
		goto free_skb;

	/* create a copy of the skb, if needed, to modify it. */
	if (skb_cow(skb, ETH_HLEN) < 0)
		goto put_orig_node;

	icmph = (struct batadv_icmp_header *)skb->data;

	/* decrement ttl */
	icmph->ttl--;

	/* route it */
	res = batadv_send_skb_to_orig(skb, orig_node, recv_if);
	if (res == NET_XMIT_SUCCESS)
		ret = NET_RX_SUCCESS;

	/* skb was consumed */
	skb = NULL;

put_orig_node:
	if (orig_node)
		batadv_orig_node_put(orig_node);
free_skb:
	kfree_skb(skb);

	return ret;
}