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
struct vlan_info {int /*<<< orphan*/  grp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vlan_info*) ; 
 int /*<<< orphan*/  vlan_group_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlan_info_free(struct vlan_info *vlan_info)
{
	vlan_group_free(&vlan_info->grp);
	kfree(vlan_info);
}