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
struct net_bridge_vlan_group {int dummy; } ;
struct net_bridge {int /*<<< orphan*/  vlgrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __vlan_flush (struct net_bridge_vlan_group*) ; 
 int /*<<< orphan*/  __vlan_group_free (struct net_bridge_vlan_group*) ; 
 struct net_bridge_vlan_group* br_vlan_group (struct net_bridge*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void br_vlan_flush(struct net_bridge *br)
{
	struct net_bridge_vlan_group *vg;

	ASSERT_RTNL();

	vg = br_vlan_group(br);
	__vlan_flush(vg);
	RCU_INIT_POINTER(br->vlgrp, NULL);
	synchronize_rcu();
	__vlan_group_free(vg);
}