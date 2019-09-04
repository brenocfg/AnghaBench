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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ priority; scalar_t__ data; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_hard_iface {int /*<<< orphan*/  batman_adv_ptype; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  soft_iface; } ;
struct batadv_frag_packet {int /*<<< orphan*/  dest; scalar_t__ priority; int /*<<< orphan*/  orig; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_CNT_FRAG_RX ; 
 int /*<<< orphan*/  BATADV_CNT_FRAG_RX_BYTES ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  batadv_add_counter (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_batman_skb_recv (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ batadv_check_unicast_packet (struct batadv_priv*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_frag_skb_buffer (struct sk_buff**,struct batadv_orig_node*) ; 
 scalar_t__ batadv_frag_skb_fwd (struct sk_buff*,struct batadv_hard_iface*,struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_inc_counter (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_is_my_mac (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 struct batadv_orig_node* batadv_orig_hash_find (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 

int batadv_recv_frag_packet(struct sk_buff *skb,
			    struct batadv_hard_iface *recv_if)
{
	struct batadv_priv *bat_priv = netdev_priv(recv_if->soft_iface);
	struct batadv_orig_node *orig_node_src = NULL;
	struct batadv_frag_packet *frag_packet;
	int ret = NET_RX_DROP;

	if (batadv_check_unicast_packet(bat_priv, skb,
					sizeof(*frag_packet)) < 0)
		goto free_skb;

	frag_packet = (struct batadv_frag_packet *)skb->data;
	orig_node_src = batadv_orig_hash_find(bat_priv, frag_packet->orig);
	if (!orig_node_src)
		goto free_skb;

	skb->priority = frag_packet->priority + 256;

	/* Route the fragment if it is not for us and too big to be merged. */
	if (!batadv_is_my_mac(bat_priv, frag_packet->dest) &&
	    batadv_frag_skb_fwd(skb, recv_if, orig_node_src)) {
		/* skb was consumed */
		skb = NULL;
		ret = NET_RX_SUCCESS;
		goto put_orig_node;
	}

	batadv_inc_counter(bat_priv, BATADV_CNT_FRAG_RX);
	batadv_add_counter(bat_priv, BATADV_CNT_FRAG_RX_BYTES, skb->len);

	/* Add fragment to buffer and merge if possible. */
	if (!batadv_frag_skb_buffer(&skb, orig_node_src))
		goto put_orig_node;

	/* Deliver merged packet to the appropriate handler, if it was
	 * merged
	 */
	if (skb) {
		batadv_batman_skb_recv(skb, recv_if->net_dev,
				       &recv_if->batman_adv_ptype, NULL);
		/* skb was consumed */
		skb = NULL;
	}

	ret = NET_RX_SUCCESS;

put_orig_node:
	batadv_orig_node_put(orig_node_src);
free_skb:
	kfree_skb(skb);

	return ret;
}