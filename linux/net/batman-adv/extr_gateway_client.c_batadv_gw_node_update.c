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
struct batadv_tvlv_gateway_data {int /*<<< orphan*/  bandwidth_down; int /*<<< orphan*/  bandwidth_up; } ;
struct TYPE_2__ {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  generation; } ;
struct batadv_priv {TYPE_1__ gw; } ;
struct batadv_orig_node {int /*<<< orphan*/  orig; } ;
struct batadv_gw_node {int bandwidth_down; int bandwidth_up; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ ,...) ; 
 struct batadv_gw_node* batadv_gw_get_selected_gw_node (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_gw_node_add (struct batadv_priv*,struct batadv_orig_node*,struct batadv_tvlv_gateway_data*) ; 
 struct batadv_gw_node* batadv_gw_node_get (struct batadv_priv*,struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_gw_node_put (struct batadv_gw_node*) ; 
 int /*<<< orphan*/  batadv_gw_reselect (struct batadv_priv*) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void batadv_gw_node_update(struct batadv_priv *bat_priv,
			   struct batadv_orig_node *orig_node,
			   struct batadv_tvlv_gateway_data *gateway)
{
	struct batadv_gw_node *gw_node, *curr_gw = NULL;

	spin_lock_bh(&bat_priv->gw.list_lock);
	gw_node = batadv_gw_node_get(bat_priv, orig_node);
	if (!gw_node) {
		batadv_gw_node_add(bat_priv, orig_node, gateway);
		spin_unlock_bh(&bat_priv->gw.list_lock);
		goto out;
	}
	spin_unlock_bh(&bat_priv->gw.list_lock);

	if (gw_node->bandwidth_down == ntohl(gateway->bandwidth_down) &&
	    gw_node->bandwidth_up == ntohl(gateway->bandwidth_up))
		goto out;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Gateway bandwidth of originator %pM changed from %u.%u/%u.%u MBit to %u.%u/%u.%u MBit\n",
		   orig_node->orig,
		   gw_node->bandwidth_down / 10,
		   gw_node->bandwidth_down % 10,
		   gw_node->bandwidth_up / 10,
		   gw_node->bandwidth_up % 10,
		   ntohl(gateway->bandwidth_down) / 10,
		   ntohl(gateway->bandwidth_down) % 10,
		   ntohl(gateway->bandwidth_up) / 10,
		   ntohl(gateway->bandwidth_up) % 10);

	gw_node->bandwidth_down = ntohl(gateway->bandwidth_down);
	gw_node->bandwidth_up = ntohl(gateway->bandwidth_up);

	if (ntohl(gateway->bandwidth_down) == 0) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Gateway %pM removed from gateway list\n",
			   orig_node->orig);

		/* Note: We don't need a NULL check here, since curr_gw never
		 * gets dereferenced.
		 */
		spin_lock_bh(&bat_priv->gw.list_lock);
		if (!hlist_unhashed(&gw_node->list)) {
			hlist_del_init_rcu(&gw_node->list);
			batadv_gw_node_put(gw_node);
			bat_priv->gw.generation++;
		}
		spin_unlock_bh(&bat_priv->gw.list_lock);

		curr_gw = batadv_gw_get_selected_gw_node(bat_priv);
		if (gw_node == curr_gw)
			batadv_gw_reselect(bat_priv);

		if (curr_gw)
			batadv_gw_node_put(curr_gw);
	}

out:
	if (gw_node)
		batadv_gw_node_put(gw_node);
}