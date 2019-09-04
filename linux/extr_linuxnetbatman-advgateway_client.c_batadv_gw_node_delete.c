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
struct batadv_tvlv_gateway_data {scalar_t__ bandwidth_up; scalar_t__ bandwidth_down; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_gw_node_update (struct batadv_priv*,struct batadv_orig_node*,struct batadv_tvlv_gateway_data*) ; 

void batadv_gw_node_delete(struct batadv_priv *bat_priv,
			   struct batadv_orig_node *orig_node)
{
	struct batadv_tvlv_gateway_data gateway;

	gateway.bandwidth_down = 0;
	gateway.bandwidth_up = 0;

	batadv_gw_node_update(bat_priv, orig_node, &gateway);
}