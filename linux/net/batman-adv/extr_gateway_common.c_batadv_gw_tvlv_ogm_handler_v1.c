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
typedef  int u8 ;
typedef  int u16 ;
struct batadv_tvlv_gateway_data {scalar_t__ bandwidth_down; scalar_t__ bandwidth_up; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct batadv_priv {TYPE_1__ gw; } ;
struct batadv_orig_node {int dummy; } ;
typedef  int /*<<< orphan*/  gateway ;

/* Variables and functions */
 scalar_t__ BATADV_GW_MODE_CLIENT ; 
 int BATADV_TVLV_HANDLER_OGM_CIFNOTFND ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_gw_check_election (struct batadv_priv*,struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_gw_node_update (struct batadv_priv*,struct batadv_orig_node*,struct batadv_tvlv_gateway_data*) ; 

__attribute__((used)) static void batadv_gw_tvlv_ogm_handler_v1(struct batadv_priv *bat_priv,
					  struct batadv_orig_node *orig,
					  u8 flags,
					  void *tvlv_value, u16 tvlv_value_len)
{
	struct batadv_tvlv_gateway_data gateway, *gateway_ptr;

	/* only fetch the tvlv value if the handler wasn't called via the
	 * CIFNOTFND flag and if there is data to fetch
	 */
	if (flags & BATADV_TVLV_HANDLER_OGM_CIFNOTFND ||
	    tvlv_value_len < sizeof(gateway)) {
		gateway.bandwidth_down = 0;
		gateway.bandwidth_up = 0;
	} else {
		gateway_ptr = tvlv_value;
		gateway.bandwidth_down = gateway_ptr->bandwidth_down;
		gateway.bandwidth_up = gateway_ptr->bandwidth_up;
		if (gateway.bandwidth_down == 0 ||
		    gateway.bandwidth_up == 0) {
			gateway.bandwidth_down = 0;
			gateway.bandwidth_up = 0;
		}
	}

	batadv_gw_node_update(bat_priv, orig, &gateway);

	/* restart gateway selection */
	if (gateway.bandwidth_down != 0 &&
	    atomic_read(&bat_priv->gw.mode) == BATADV_GW_MODE_CLIENT)
		batadv_gw_check_election(bat_priv, orig);
}