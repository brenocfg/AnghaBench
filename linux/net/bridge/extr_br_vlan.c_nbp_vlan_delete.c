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
struct net_bridge_vlan {int dummy; } ;
struct net_bridge_port {int /*<<< orphan*/  br; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOENT ; 
 int __vlan_del (struct net_bridge_vlan*) ; 
 int /*<<< orphan*/  br_fdb_delete_by_port (int /*<<< orphan*/ ,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_fdb_find_delete_local (int /*<<< orphan*/ ,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_bridge_vlan* br_vlan_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nbp_vlan_group (struct net_bridge_port*) ; 

int nbp_vlan_delete(struct net_bridge_port *port, u16 vid)
{
	struct net_bridge_vlan *v;

	ASSERT_RTNL();

	v = br_vlan_find(nbp_vlan_group(port), vid);
	if (!v)
		return -ENOENT;
	br_fdb_find_delete_local(port->br, port, port->dev->dev_addr, vid);
	br_fdb_delete_by_port(port->br, port, vid, 0);

	return __vlan_del(v);
}