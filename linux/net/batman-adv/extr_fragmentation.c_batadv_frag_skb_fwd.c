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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_neigh_node {TYPE_2__* if_incoming; } ;
struct batadv_hard_iface {int /*<<< orphan*/  soft_iface; } ;
struct batadv_frag_packet {int /*<<< orphan*/  ttl; int /*<<< orphan*/  total_size; int /*<<< orphan*/  dest; } ;
struct TYPE_4__ {TYPE_1__* net_dev; } ;
struct TYPE_3__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_CNT_FRAG_FWD ; 
 int /*<<< orphan*/  BATADV_CNT_FRAG_FWD_BYTES ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  batadv_add_counter (struct batadv_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct batadv_neigh_node* batadv_find_router (struct batadv_priv*,struct batadv_orig_node*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_inc_counter (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_neigh_node_put (struct batadv_neigh_node*) ; 
 struct batadv_orig_node* batadv_orig_hash_find (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_send_unicast_skb (struct sk_buff*,struct batadv_neigh_node*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

bool batadv_frag_skb_fwd(struct sk_buff *skb,
			 struct batadv_hard_iface *recv_if,
			 struct batadv_orig_node *orig_node_src)
{
	struct batadv_priv *bat_priv = netdev_priv(recv_if->soft_iface);
	struct batadv_orig_node *orig_node_dst;
	struct batadv_neigh_node *neigh_node = NULL;
	struct batadv_frag_packet *packet;
	u16 total_size;
	bool ret = false;

	packet = (struct batadv_frag_packet *)skb->data;
	orig_node_dst = batadv_orig_hash_find(bat_priv, packet->dest);
	if (!orig_node_dst)
		goto out;

	neigh_node = batadv_find_router(bat_priv, orig_node_dst, recv_if);
	if (!neigh_node)
		goto out;

	/* Forward the fragment, if the merged packet would be too big to
	 * be assembled.
	 */
	total_size = ntohs(packet->total_size);
	if (total_size > neigh_node->if_incoming->net_dev->mtu) {
		batadv_inc_counter(bat_priv, BATADV_CNT_FRAG_FWD);
		batadv_add_counter(bat_priv, BATADV_CNT_FRAG_FWD_BYTES,
				   skb->len + ETH_HLEN);

		packet->ttl--;
		batadv_send_unicast_skb(skb, neigh_node);
		ret = true;
	}

out:
	if (orig_node_dst)
		batadv_orig_node_put(orig_node_dst);
	if (neigh_node)
		batadv_neigh_node_put(neigh_node);
	return ret;
}