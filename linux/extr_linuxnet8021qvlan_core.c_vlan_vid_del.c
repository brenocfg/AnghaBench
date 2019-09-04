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
struct vlan_vid_info {scalar_t__ refcount; } ;
struct vlan_info {scalar_t__ nr_vids; int /*<<< orphan*/  rcu; } ;
struct net_device {int /*<<< orphan*/  vlan_info; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __vlan_vid_del (struct vlan_info*,struct vlan_vid_info*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vlan_info* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_info_rcu_free ; 
 struct vlan_vid_info* vlan_vid_info_get (struct vlan_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vlan_vid_del(struct net_device *dev, __be16 proto, u16 vid)
{
	struct vlan_info *vlan_info;
	struct vlan_vid_info *vid_info;

	ASSERT_RTNL();

	vlan_info = rtnl_dereference(dev->vlan_info);
	if (!vlan_info)
		return;

	vid_info = vlan_vid_info_get(vlan_info, proto, vid);
	if (!vid_info)
		return;
	vid_info->refcount--;
	if (vid_info->refcount == 0) {
		__vlan_vid_del(vlan_info, vid_info);
		if (vlan_info->nr_vids == 0) {
			RCU_INIT_POINTER(dev->vlan_info, NULL);
			call_rcu(&vlan_info->rcu, vlan_info_rcu_free);
		}
	}
}