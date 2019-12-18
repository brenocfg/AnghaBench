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
struct net_device {int dummy; } ;
struct batadv_priv {int dummy; } ;
struct batadv_hard_iface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_bla_update_orig_address (struct batadv_priv*,struct batadv_hard_iface*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 

void batadv_bla_status_update(struct net_device *net_dev)
{
	struct batadv_priv *bat_priv = netdev_priv(net_dev);
	struct batadv_hard_iface *primary_if;

	primary_if = batadv_primary_if_get_selected(bat_priv);
	if (!primary_if)
		return;

	/* this function already purges everything when bla is disabled,
	 * so just call that one.
	 */
	batadv_bla_update_orig_address(bat_priv, primary_if, primary_if);
	batadv_hardif_put(primary_if);
}