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
struct sk_buff {scalar_t__ data; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;
struct batadv_unicast_packet {scalar_t__ ttvn; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;

/* Variables and functions */
#define  BATADV_UNICAST 129 
#define  BATADV_UNICAST_4ADDR 128 
 int NET_XMIT_DROP ; 
 int /*<<< orphan*/  batadv_send_skb_prepare_unicast (struct sk_buff*,struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_send_skb_prepare_unicast_4addr (struct batadv_priv*,struct sk_buff*,struct batadv_orig_node*,int) ; 
 int batadv_send_skb_to_orig (struct sk_buff*,struct batadv_orig_node*,int /*<<< orphan*/ *) ; 
 scalar_t__ batadv_tt_global_client_is_roaming (struct batadv_priv*,int /*<<< orphan*/ ,unsigned short) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

int batadv_send_skb_unicast(struct batadv_priv *bat_priv,
			    struct sk_buff *skb, int packet_type,
			    int packet_subtype,
			    struct batadv_orig_node *orig_node,
			    unsigned short vid)
{
	struct batadv_unicast_packet *unicast_packet;
	struct ethhdr *ethhdr;
	int ret = NET_XMIT_DROP;

	if (!orig_node)
		goto out;

	switch (packet_type) {
	case BATADV_UNICAST:
		if (!batadv_send_skb_prepare_unicast(skb, orig_node))
			goto out;
		break;
	case BATADV_UNICAST_4ADDR:
		if (!batadv_send_skb_prepare_unicast_4addr(bat_priv, skb,
							   orig_node,
							   packet_subtype))
			goto out;
		break;
	default:
		/* this function supports UNICAST and UNICAST_4ADDR only. It
		 * should never be invoked with any other packet type
		 */
		goto out;
	}

	/* skb->data might have been reallocated by
	 * batadv_send_skb_prepare_unicast{,_4addr}()
	 */
	ethhdr = eth_hdr(skb);
	unicast_packet = (struct batadv_unicast_packet *)skb->data;

	/* inform the destination node that we are still missing a correct route
	 * for this client. The destination will receive this packet and will
	 * try to reroute it because the ttvn contained in the header is less
	 * than the current one
	 */
	if (batadv_tt_global_client_is_roaming(bat_priv, ethhdr->h_dest, vid))
		unicast_packet->ttvn = unicast_packet->ttvn - 1;

	ret = batadv_send_skb_to_orig(skb, orig_node, NULL);
	 /* skb was consumed */
	skb = NULL;

out:
	kfree_skb(skb);
	return ret;
}