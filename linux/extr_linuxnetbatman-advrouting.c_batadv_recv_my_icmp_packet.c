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
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  len; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_icmp_tp_packet {int dummy; } ;
struct batadv_icmp_header {int msg_type; int /*<<< orphan*/  ttl; int /*<<< orphan*/  orig; int /*<<< orphan*/  dst; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
#define  BATADV_DESTINATION_UNREACHABLE 132 
#define  BATADV_ECHO_REPLY 131 
#define  BATADV_ECHO_REQUEST 130 
#define  BATADV_TP 129 
 int /*<<< orphan*/  BATADV_TTL ; 
#define  BATADV_TTL_EXCEEDED 128 
 int /*<<< orphan*/  ETH_HLEN ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 struct batadv_orig_node* batadv_orig_hash_find (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 int batadv_send_skb_to_orig (struct sk_buff*,struct batadv_orig_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_socket_receive_packet (struct batadv_icmp_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tp_meter_recv (struct batadv_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_cow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_linearize (struct sk_buff*) ; 

__attribute__((used)) static int batadv_recv_my_icmp_packet(struct batadv_priv *bat_priv,
				      struct sk_buff *skb)
{
	struct batadv_hard_iface *primary_if = NULL;
	struct batadv_orig_node *orig_node = NULL;
	struct batadv_icmp_header *icmph;
	int res, ret = NET_RX_DROP;

	icmph = (struct batadv_icmp_header *)skb->data;

	switch (icmph->msg_type) {
	case BATADV_ECHO_REPLY:
	case BATADV_DESTINATION_UNREACHABLE:
	case BATADV_TTL_EXCEEDED:
		/* receive the packet */
		if (skb_linearize(skb) < 0)
			break;

		batadv_socket_receive_packet(icmph, skb->len);
		break;
	case BATADV_ECHO_REQUEST:
		/* answer echo request (ping) */
		primary_if = batadv_primary_if_get_selected(bat_priv);
		if (!primary_if)
			goto out;

		/* get routing information */
		orig_node = batadv_orig_hash_find(bat_priv, icmph->orig);
		if (!orig_node)
			goto out;

		/* create a copy of the skb, if needed, to modify it. */
		if (skb_cow(skb, ETH_HLEN) < 0)
			goto out;

		icmph = (struct batadv_icmp_header *)skb->data;

		ether_addr_copy(icmph->dst, icmph->orig);
		ether_addr_copy(icmph->orig, primary_if->net_dev->dev_addr);
		icmph->msg_type = BATADV_ECHO_REPLY;
		icmph->ttl = BATADV_TTL;

		res = batadv_send_skb_to_orig(skb, orig_node, NULL);
		if (res == NET_XMIT_SUCCESS)
			ret = NET_RX_SUCCESS;

		/* skb was consumed */
		skb = NULL;
		break;
	case BATADV_TP:
		if (!pskb_may_pull(skb, sizeof(struct batadv_icmp_tp_packet)))
			goto out;

		batadv_tp_meter_recv(bat_priv, skb);
		ret = NET_RX_SUCCESS;
		/* skb was consumed */
		skb = NULL;
		goto out;
	default:
		/* drop unknown type */
		goto out;
	}
out:
	if (primary_if)
		batadv_hardif_put(primary_if);
	if (orig_node)
		batadv_orig_node_put(orig_node);

	kfree_skb(skb);

	return ret;
}