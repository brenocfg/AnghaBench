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
typedef  size_t u16 ;
struct vlan_group {struct net_device**** vlan_devices_arrays; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 size_t VLAN_GROUP_ARRAY_PART_LEN ; 
 size_t vlan_proto_idx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vlan_group_set_device(struct vlan_group *vg,
					 __be16 vlan_proto, u16 vlan_id,
					 struct net_device *dev)
{
	struct net_device **array;
	if (!vg)
		return;
	array = vg->vlan_devices_arrays[vlan_proto_idx(vlan_proto)]
				       [vlan_id / VLAN_GROUP_ARRAY_PART_LEN];
	array[vlan_id % VLAN_GROUP_ARRAY_PART_LEN] = dev;
}