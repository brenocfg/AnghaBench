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
typedef  int /*<<< orphan*/  u16 ;
struct vlan_info {int /*<<< orphan*/  grp; } ;
struct net_device {int /*<<< orphan*/  vlan_info; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct net_device* netdev_master_upper_dev_get_rcu (struct net_device*) ; 
 struct vlan_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct net_device* vlan_group_get_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct net_device *__vlan_find_dev_deep_rcu(struct net_device *dev,
					__be16 vlan_proto, u16 vlan_id)
{
	struct vlan_info *vlan_info = rcu_dereference(dev->vlan_info);

	if (vlan_info) {
		return vlan_group_get_device(&vlan_info->grp,
					     vlan_proto, vlan_id);
	} else {
		/*
		 * Lower devices of master uppers (bonding, team) do not have
		 * grp assigned to themselves. Grp is assigned to upper device
		 * instead.
		 */
		struct net_device *upper_dev;

		upper_dev = netdev_master_upper_dev_get_rcu(dev);
		if (upper_dev)
			return __vlan_find_dev_deep_rcu(upper_dev,
						    vlan_proto, vlan_id);
	}

	return NULL;
}