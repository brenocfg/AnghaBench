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
struct sk_buff {int dummy; } ;
struct batadv_neigh_node {int /*<<< orphan*/  addr; int /*<<< orphan*/  if_incoming; } ;

/* Variables and functions */
 int batadv_send_skb_packet (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int batadv_send_unicast_skb(struct sk_buff *skb,
			    struct batadv_neigh_node *neigh)
{
#ifdef CONFIG_BATMAN_ADV_BATMAN_V
	struct batadv_hardif_neigh_node *hardif_neigh;
#endif
	int ret;

	ret = batadv_send_skb_packet(skb, neigh->if_incoming, neigh->addr);

#ifdef CONFIG_BATMAN_ADV_BATMAN_V
	hardif_neigh = batadv_hardif_neigh_get(neigh->if_incoming, neigh->addr);

	if (hardif_neigh && ret != NET_XMIT_DROP)
		hardif_neigh->bat_v.last_unicast_tx = jiffies;

	if (hardif_neigh)
		batadv_hardif_neigh_put(hardif_neigh);
#endif

	return ret;
}