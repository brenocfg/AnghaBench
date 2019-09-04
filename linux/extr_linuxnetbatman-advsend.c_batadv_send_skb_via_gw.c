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
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_P_DATA ; 
 int /*<<< orphan*/  BATADV_UNICAST_4ADDR ; 
 struct batadv_orig_node* batadv_gw_get_selected_orig (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 int batadv_send_skb_unicast (struct batadv_priv*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct batadv_orig_node*,unsigned short) ; 

int batadv_send_skb_via_gw(struct batadv_priv *bat_priv, struct sk_buff *skb,
			   unsigned short vid)
{
	struct batadv_orig_node *orig_node;
	int ret;

	orig_node = batadv_gw_get_selected_orig(bat_priv);
	ret = batadv_send_skb_unicast(bat_priv, skb, BATADV_UNICAST_4ADDR,
				      BATADV_P_DATA, orig_node, vid);

	if (orig_node)
		batadv_orig_node_put(orig_node);

	return ret;
}