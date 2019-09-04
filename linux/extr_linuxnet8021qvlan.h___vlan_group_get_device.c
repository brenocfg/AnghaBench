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

/* Variables and functions */
 size_t VLAN_GROUP_ARRAY_PART_LEN ; 

__attribute__((used)) static inline struct net_device *__vlan_group_get_device(struct vlan_group *vg,
							 unsigned int pidx,
							 u16 vlan_id)
{
	struct net_device **array;

	array = vg->vlan_devices_arrays[pidx]
				       [vlan_id / VLAN_GROUP_ARRAY_PART_LEN];
	return array ? array[vlan_id % VLAN_GROUP_ARRAY_PART_LEN] : NULL;
}