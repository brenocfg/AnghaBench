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
struct batadv_priv {int /*<<< orphan*/ * mesh_obj; } ;
struct batadv_attribute {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 struct batadv_attribute** batadv_mesh_attrs ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void batadv_sysfs_del_meshif(struct net_device *dev)
{
	struct batadv_priv *bat_priv = netdev_priv(dev);
	struct batadv_attribute **bat_attr;

	for (bat_attr = batadv_mesh_attrs; *bat_attr; ++bat_attr)
		sysfs_remove_file(bat_priv->mesh_obj, &((*bat_attr)->attr));

	kobject_uevent(bat_priv->mesh_obj, KOBJ_REMOVE);
	kobject_del(bat_priv->mesh_obj);
	kobject_put(bat_priv->mesh_obj);
	bat_priv->mesh_obj = NULL;
}