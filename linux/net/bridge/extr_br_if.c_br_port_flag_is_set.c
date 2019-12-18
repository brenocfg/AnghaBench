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
struct net_device {int dummy; } ;
struct net_bridge_port {unsigned long flags; } ;

/* Variables and functions */
 struct net_bridge_port* br_port_get_rtnl_rcu (struct net_device const*) ; 

bool br_port_flag_is_set(const struct net_device *dev, unsigned long flag)
{
	struct net_bridge_port *p;

	p = br_port_get_rtnl_rcu(dev);
	if (!p)
		return false;

	return p->flags & flag;
}