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
struct sk_buff {scalar_t__ len; } ;
struct batadv_priv {int /*<<< orphan*/  fragmentation; } ;
struct batadv_orig_node {struct batadv_priv* bat_priv; } ;
struct batadv_neigh_node {TYPE_2__* if_incoming; } ;
struct batadv_hard_iface {int dummy; } ;
struct TYPE_4__ {TYPE_1__* net_dev; } ;
struct TYPE_3__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct batadv_neigh_node* batadv_find_router (struct batadv_priv*,struct batadv_orig_node*,struct batadv_hard_iface*) ; 
 int batadv_frag_send_packet (struct sk_buff*,struct batadv_orig_node*,struct batadv_neigh_node*) ; 
 scalar_t__ batadv_nc_skb_forward (struct sk_buff*,struct batadv_neigh_node*) ; 
 int /*<<< orphan*/  batadv_neigh_node_put (struct batadv_neigh_node*) ; 
 int batadv_send_unicast_skb (struct sk_buff*,struct batadv_neigh_node*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

int batadv_send_skb_to_orig(struct sk_buff *skb,
			    struct batadv_orig_node *orig_node,
			    struct batadv_hard_iface *recv_if)
{
	struct batadv_priv *bat_priv = orig_node->bat_priv;
	struct batadv_neigh_node *neigh_node;
	int ret;

	/* batadv_find_router() increases neigh_nodes refcount if found. */
	neigh_node = batadv_find_router(bat_priv, orig_node, recv_if);
	if (!neigh_node) {
		ret = -EINVAL;
		goto free_skb;
	}

	/* Check if the skb is too large to send in one piece and fragment
	 * it if needed.
	 */
	if (atomic_read(&bat_priv->fragmentation) &&
	    skb->len > neigh_node->if_incoming->net_dev->mtu) {
		/* Fragment and send packet. */
		ret = batadv_frag_send_packet(skb, orig_node, neigh_node);
		/* skb was consumed */
		skb = NULL;

		goto put_neigh_node;
	}

	/* try to network code the packet, if it is received on an interface
	 * (i.e. being forwarded). If the packet originates from this node or if
	 * network coding fails, then send the packet as usual.
	 */
	if (recv_if && batadv_nc_skb_forward(skb, neigh_node))
		ret = -EINPROGRESS;
	else
		ret = batadv_send_unicast_skb(skb, neigh_node);

	/* skb was consumed */
	skb = NULL;

put_neigh_node:
	batadv_neigh_node_put(neigh_node);
free_skb:
	kfree_skb(skb);

	return ret;
}