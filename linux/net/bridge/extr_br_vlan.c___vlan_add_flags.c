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
struct net_bridge_vlan_group {int dummy; } ;
struct net_bridge_vlan {int flags; int /*<<< orphan*/  vid; int /*<<< orphan*/  port; int /*<<< orphan*/  br; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_PVID ; 
 int BRIDGE_VLAN_INFO_UNTAGGED ; 
 int __vlan_add_pvid (struct net_bridge_vlan_group*,int /*<<< orphan*/ ) ; 
 int __vlan_delete_pvid (struct net_bridge_vlan_group*,int /*<<< orphan*/ ) ; 
 struct net_bridge_vlan_group* br_vlan_group (int /*<<< orphan*/ ) ; 
 scalar_t__ br_vlan_is_master (struct net_bridge_vlan*) ; 
 struct net_bridge_vlan_group* nbp_vlan_group (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __vlan_add_flags(struct net_bridge_vlan *v, u16 flags)
{
	struct net_bridge_vlan_group *vg;
	u16 old_flags = v->flags;
	bool ret;

	if (br_vlan_is_master(v))
		vg = br_vlan_group(v->br);
	else
		vg = nbp_vlan_group(v->port);

	if (flags & BRIDGE_VLAN_INFO_PVID)
		ret = __vlan_add_pvid(vg, v->vid);
	else
		ret = __vlan_delete_pvid(vg, v->vid);

	if (flags & BRIDGE_VLAN_INFO_UNTAGGED)
		v->flags |= BRIDGE_VLAN_INFO_UNTAGGED;
	else
		v->flags &= ~BRIDGE_VLAN_INFO_UNTAGGED;

	return ret || !!(old_flags ^ v->flags);
}