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
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct batadv_priv {TYPE_1__ gw; } ;
struct batadv_gw_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ BATADV_GW_MODE_CLIENT ; 
 int /*<<< orphan*/  BATADV_UEV_DEL ; 
 int /*<<< orphan*/  BATADV_UEV_GW ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct batadv_gw_node* batadv_gw_get_selected_gw_node (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_gw_node_put (struct batadv_gw_node*) ; 
 int /*<<< orphan*/  batadv_gw_select (struct batadv_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_throw_uevent (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void batadv_gw_check_client_stop(struct batadv_priv *bat_priv)
{
	struct batadv_gw_node *curr_gw;

	if (atomic_read(&bat_priv->gw.mode) != BATADV_GW_MODE_CLIENT)
		return;

	curr_gw = batadv_gw_get_selected_gw_node(bat_priv);
	if (!curr_gw)
		return;

	/* deselect the current gateway so that next time that client mode is
	 * enabled a proper GW_ADD event can be sent
	 */
	batadv_gw_select(bat_priv, NULL);

	/* if batman-adv is switching the gw client mode off and a gateway was
	 * already selected, send a DEL uevent
	 */
	batadv_throw_uevent(bat_priv, BATADV_UEV_GW, BATADV_UEV_DEL, NULL);

	batadv_gw_node_put(curr_gw);
}