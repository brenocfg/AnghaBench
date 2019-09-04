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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct ethhdr {int /*<<< orphan*/ * h_dest; int /*<<< orphan*/ * h_source; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 int batadv_send_skb_unicast (struct batadv_priv*,struct sk_buff*,int,int,struct batadv_orig_node*,unsigned short) ; 
 struct batadv_orig_node* batadv_transtable_search (struct batadv_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned short) ; 

int batadv_send_skb_via_tt_generic(struct batadv_priv *bat_priv,
				   struct sk_buff *skb, int packet_type,
				   int packet_subtype, u8 *dst_hint,
				   unsigned short vid)
{
	struct ethhdr *ethhdr = (struct ethhdr *)skb->data;
	struct batadv_orig_node *orig_node;
	u8 *src, *dst;
	int ret;

	src = ethhdr->h_source;
	dst = ethhdr->h_dest;

	/* if we got an hint! let's send the packet to this client (if any) */
	if (dst_hint) {
		src = NULL;
		dst = dst_hint;
	}
	orig_node = batadv_transtable_search(bat_priv, src, dst, vid);

	ret = batadv_send_skb_unicast(bat_priv, skb, packet_type,
				      packet_subtype, orig_node, vid);

	if (orig_node)
		batadv_orig_node_put(orig_node);

	return ret;
}