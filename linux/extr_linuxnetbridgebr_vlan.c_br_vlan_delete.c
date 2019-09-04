#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct net_bridge_vlan_group {int dummy; } ;
struct net_bridge_vlan {int dummy; } ;
struct net_bridge {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOENT ; 
 int __vlan_del (struct net_bridge_vlan*) ; 
 int /*<<< orphan*/  br_fdb_delete_by_port (struct net_bridge*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_fdb_find_delete_local (struct net_bridge*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_bridge_vlan* br_vlan_find (struct net_bridge_vlan_group*,int /*<<< orphan*/ ) ; 
 struct net_bridge_vlan_group* br_vlan_group (struct net_bridge*) ; 
 int /*<<< orphan*/  br_vlan_is_brentry (struct net_bridge_vlan*) ; 
 int /*<<< orphan*/  vlan_tunnel_info_del (struct net_bridge_vlan_group*,struct net_bridge_vlan*) ; 

int br_vlan_delete(struct net_bridge *br, u16 vid)
{
	struct net_bridge_vlan_group *vg;
	struct net_bridge_vlan *v;

	ASSERT_RTNL();

	vg = br_vlan_group(br);
	v = br_vlan_find(vg, vid);
	if (!v || !br_vlan_is_brentry(v))
		return -ENOENT;

	br_fdb_find_delete_local(br, NULL, br->dev->dev_addr, vid);
	br_fdb_delete_by_port(br, NULL, vid, 0);

	vlan_tunnel_info_del(vg, v);

	return __vlan_del(v);
}