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
struct vlan_group {int /*<<< orphan*/ ** vlan_devices_arrays; } ;

/* Variables and functions */
 int VLAN_GROUP_ARRAY_SPLIT_PARTS ; 
 int VLAN_PROTO_NUM ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlan_group_free(struct vlan_group *grp)
{
	int i, j;

	for (i = 0; i < VLAN_PROTO_NUM; i++)
		for (j = 0; j < VLAN_GROUP_ARRAY_SPLIT_PARTS; j++)
			kfree(grp->vlan_devices_arrays[i][j]);
}