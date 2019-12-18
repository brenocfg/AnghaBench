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
struct batadv_softif_vlan {int /*<<< orphan*/  vid; } ;
struct batadv_priv {TYPE_1__* soft_iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_softif_vlan_put (struct batadv_softif_vlan*) ; 
 int /*<<< orphan*/  batadv_sysfs_del_vlan (struct batadv_priv*,struct batadv_softif_vlan*) ; 
 int /*<<< orphan*/  batadv_tt_local_remove (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void batadv_softif_destroy_vlan(struct batadv_priv *bat_priv,
				       struct batadv_softif_vlan *vlan)
{
	/* explicitly remove the associated TT local entry because it is marked
	 * with the NOPURGE flag
	 */
	batadv_tt_local_remove(bat_priv, bat_priv->soft_iface->dev_addr,
			       vlan->vid, "vlan interface destroyed", false);

	batadv_sysfs_del_vlan(bat_priv, vlan);
	batadv_softif_vlan_put(vlan);
}