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
typedef  int u16 ;
struct vlan_group {struct net_device**** vlan_devices_arrays; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VLAN_GROUP_ARRAY_PART_LEN ; 
 struct net_device** kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int vlan_proto_idx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlan_group_prealloc_vid(struct vlan_group *vg,
				   __be16 vlan_proto, u16 vlan_id)
{
	struct net_device **array;
	unsigned int pidx, vidx;
	unsigned int size;

	ASSERT_RTNL();

	pidx  = vlan_proto_idx(vlan_proto);
	vidx  = vlan_id / VLAN_GROUP_ARRAY_PART_LEN;
	array = vg->vlan_devices_arrays[pidx][vidx];
	if (array != NULL)
		return 0;

	size = sizeof(struct net_device *) * VLAN_GROUP_ARRAY_PART_LEN;
	array = kzalloc(size, GFP_KERNEL);
	if (array == NULL)
		return -ENOBUFS;

	vg->vlan_devices_arrays[pidx][vidx] = array;
	return 0;
}