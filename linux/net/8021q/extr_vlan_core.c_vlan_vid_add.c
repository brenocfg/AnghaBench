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
struct vlan_vid_info {int /*<<< orphan*/  refcount; } ;
struct vlan_info {int dummy; } ;
struct net_device {int /*<<< orphan*/  vlan_info; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOMEM ; 
 int __vlan_vid_add (struct vlan_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vlan_vid_info**) ; 
 int /*<<< orphan*/  kfree (struct vlan_info*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct vlan_info*) ; 
 struct vlan_info* rtnl_dereference (int /*<<< orphan*/ ) ; 
 struct vlan_info* vlan_info_alloc (struct net_device*) ; 
 struct vlan_vid_info* vlan_vid_info_get (struct vlan_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vlan_vid_add(struct net_device *dev, __be16 proto, u16 vid)
{
	struct vlan_info *vlan_info;
	struct vlan_vid_info *vid_info;
	bool vlan_info_created = false;
	int err;

	ASSERT_RTNL();

	vlan_info = rtnl_dereference(dev->vlan_info);
	if (!vlan_info) {
		vlan_info = vlan_info_alloc(dev);
		if (!vlan_info)
			return -ENOMEM;
		vlan_info_created = true;
	}
	vid_info = vlan_vid_info_get(vlan_info, proto, vid);
	if (!vid_info) {
		err = __vlan_vid_add(vlan_info, proto, vid, &vid_info);
		if (err)
			goto out_free_vlan_info;
	}
	vid_info->refcount++;

	if (vlan_info_created)
		rcu_assign_pointer(dev->vlan_info, vlan_info);

	return 0;

out_free_vlan_info:
	if (vlan_info_created)
		kfree(vlan_info);
	return err;
}