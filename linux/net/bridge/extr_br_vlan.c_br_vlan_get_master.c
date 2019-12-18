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
struct netlink_ext_ack {int dummy; } ;
struct net_bridge_vlan_group {int dummy; } ;
struct net_bridge_vlan {int /*<<< orphan*/  refcnt; } ;
struct net_bridge {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ br_vlan_add (struct net_bridge*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct netlink_ext_ack*) ; 
 struct net_bridge_vlan* br_vlan_find (struct net_bridge_vlan_group*,int /*<<< orphan*/ ) ; 
 struct net_bridge_vlan_group* br_vlan_group (struct net_bridge*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct net_bridge_vlan *
br_vlan_get_master(struct net_bridge *br, u16 vid,
		   struct netlink_ext_ack *extack)
{
	struct net_bridge_vlan_group *vg;
	struct net_bridge_vlan *masterv;

	vg = br_vlan_group(br);
	masterv = br_vlan_find(vg, vid);
	if (!masterv) {
		bool changed;

		/* missing global ctx, create it now */
		if (br_vlan_add(br, vid, 0, &changed, extack))
			return NULL;
		masterv = br_vlan_find(vg, vid);
		if (WARN_ON(!masterv))
			return NULL;
		refcount_set(&masterv->refcnt, 1);
		return masterv;
	}
	refcount_inc(&masterv->refcnt);

	return masterv;
}