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
 struct vlan_info* rcu_dereference_rtnl (int /*<<< orphan*/ ) ; 
 struct net_device* vlan_group_get_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct net_device *vlan_find_dev(struct net_device *real_dev,
					       __be16 vlan_proto, u16 vlan_id)
{
	struct vlan_info *vlan_info = rcu_dereference_rtnl(real_dev->vlan_info);

	if (vlan_info)
		return vlan_group_get_device(&vlan_info->grp,
					     vlan_proto, vlan_id);

	return NULL;
}