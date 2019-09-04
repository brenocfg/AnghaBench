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
struct batadv_unicast_packet {int /*<<< orphan*/  dest; } ;
struct batadv_priv {int dummy; } ;
struct batadv_hard_iface {int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int batadv_check_unicast_packet (struct batadv_priv*,struct sk_buff*,int) ; 
 scalar_t__ batadv_is_my_mac (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int batadv_route_unicast_packet (struct sk_buff*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 

int batadv_recv_unhandled_unicast_packet(struct sk_buff *skb,
					 struct batadv_hard_iface *recv_if)
{
	struct batadv_unicast_packet *unicast_packet;
	struct batadv_priv *bat_priv = netdev_priv(recv_if->soft_iface);
	int check, hdr_size = sizeof(*unicast_packet);

	check = batadv_check_unicast_packet(bat_priv, skb, hdr_size);
	if (check < 0)
		goto free_skb;

	/* we don't know about this type, drop it. */
	unicast_packet = (struct batadv_unicast_packet *)skb->data;
	if (batadv_is_my_mac(bat_priv, unicast_packet->dest))
		goto free_skb;

	return batadv_route_unicast_packet(skb, recv_if);

free_skb:
	kfree_skb(skb);
	return NET_RX_DROP;
}