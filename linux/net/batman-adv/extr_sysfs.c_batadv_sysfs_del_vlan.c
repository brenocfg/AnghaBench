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
struct batadv_softif_vlan {int /*<<< orphan*/ * kobj; } ;
struct batadv_priv {int /*<<< orphan*/ * mesh_obj; } ;
struct batadv_attribute {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 struct batadv_attribute** batadv_vlan_attrs ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void batadv_sysfs_del_vlan(struct batadv_priv *bat_priv,
			   struct batadv_softif_vlan *vlan)
{
	struct batadv_attribute **bat_attr;

	for (bat_attr = batadv_vlan_attrs; *bat_attr; ++bat_attr)
		sysfs_remove_file(vlan->kobj, &((*bat_attr)->attr));

	if (vlan->kobj != bat_priv->mesh_obj) {
		kobject_uevent(vlan->kobj, KOBJ_REMOVE);
		kobject_del(vlan->kobj);
	}
	kobject_put(vlan->kobj);
	vlan->kobj = NULL;
}