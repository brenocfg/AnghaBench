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
struct sk_buff {unsigned int len; scalar_t__ data; } ;
struct ethhdr {int /*<<< orphan*/  h_source; } ;
struct batadv_unicast_packet {int ttl; int packet_type; int /*<<< orphan*/  dest; } ;
struct batadv_unicast_4addr_packet {int dummy; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_hard_iface {int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_CNT_FORWARD ; 
 int /*<<< orphan*/  BATADV_CNT_FORWARD_BYTES ; 
#define  BATADV_UNICAST 129 
#define  BATADV_UNICAST_4ADDR 128 
 scalar_t__ ETH_HLEN ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  batadv_add_counter (struct batadv_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  batadv_inc_counter (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 struct batadv_orig_node* batadv_orig_hash_find (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 int batadv_send_skb_to_orig (struct sk_buff*,struct batadv_orig_node*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_skb_set_priority (struct sk_buff*,int) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cow (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int batadv_route_unicast_packet(struct sk_buff *skb,
				       struct batadv_hard_iface *recv_if)
{
	struct batadv_priv *bat_priv = netdev_priv(recv_if->soft_iface);
	struct batadv_orig_node *orig_node = NULL;
	struct batadv_unicast_packet *unicast_packet;
	struct ethhdr *ethhdr = eth_hdr(skb);
	int res, hdr_len, ret = NET_RX_DROP;
	unsigned int len;

	unicast_packet = (struct batadv_unicast_packet *)skb->data;

	/* TTL exceeded */
	if (unicast_packet->ttl < 2) {
		pr_debug("Warning - can't forward unicast packet from %pM to %pM: ttl exceeded\n",
			 ethhdr->h_source, unicast_packet->dest);
		goto free_skb;
	}

	/* get routing information */
	orig_node = batadv_orig_hash_find(bat_priv, unicast_packet->dest);

	if (!orig_node)
		goto free_skb;

	/* create a copy of the skb, if needed, to modify it. */
	if (skb_cow(skb, ETH_HLEN) < 0)
		goto put_orig_node;

	/* decrement ttl */
	unicast_packet = (struct batadv_unicast_packet *)skb->data;
	unicast_packet->ttl--;

	switch (unicast_packet->packet_type) {
	case BATADV_UNICAST_4ADDR:
		hdr_len = sizeof(struct batadv_unicast_4addr_packet);
		break;
	case BATADV_UNICAST:
		hdr_len = sizeof(struct batadv_unicast_packet);
		break;
	default:
		/* other packet types not supported - yet */
		hdr_len = -1;
		break;
	}

	if (hdr_len > 0)
		batadv_skb_set_priority(skb, hdr_len);

	len = skb->len;
	res = batadv_send_skb_to_orig(skb, orig_node, recv_if);

	/* translate transmit result into receive result */
	if (res == NET_XMIT_SUCCESS) {
		ret = NET_RX_SUCCESS;
		/* skb was transmitted and consumed */
		batadv_inc_counter(bat_priv, BATADV_CNT_FORWARD);
		batadv_add_counter(bat_priv, BATADV_CNT_FORWARD_BYTES,
				   len + ETH_HLEN);
	}

	/* skb was consumed */
	skb = NULL;

put_orig_node:
	batadv_orig_node_put(orig_node);
free_skb:
	kfree_skb(skb);

	return ret;
}