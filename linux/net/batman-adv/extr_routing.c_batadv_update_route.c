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
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_neigh_node {int dummy; } ;
struct batadv_hard_iface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _batadv_update_route (struct batadv_priv*,struct batadv_orig_node*,struct batadv_hard_iface*,struct batadv_neigh_node*) ; 
 int /*<<< orphan*/  batadv_neigh_node_put (struct batadv_neigh_node*) ; 
 struct batadv_neigh_node* batadv_orig_router_get (struct batadv_orig_node*,struct batadv_hard_iface*) ; 

void batadv_update_route(struct batadv_priv *bat_priv,
			 struct batadv_orig_node *orig_node,
			 struct batadv_hard_iface *recv_if,
			 struct batadv_neigh_node *neigh_node)
{
	struct batadv_neigh_node *router = NULL;

	if (!orig_node)
		goto out;

	router = batadv_orig_router_get(orig_node, recv_if);

	if (router != neigh_node)
		_batadv_update_route(bat_priv, orig_node, recv_if, neigh_node);

out:
	if (router)
		batadv_neigh_node_put(router);
}