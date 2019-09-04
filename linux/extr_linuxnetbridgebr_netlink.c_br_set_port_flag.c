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
struct nlattr {int dummy; } ;
struct net_bridge_port {unsigned long flags; } ;

/* Variables and functions */
 int br_switchdev_set_port_flag (struct net_bridge_port*,unsigned long,unsigned long) ; 
 scalar_t__ nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static int br_set_port_flag(struct net_bridge_port *p, struct nlattr *tb[],
			    int attrtype, unsigned long mask)
{
	unsigned long flags;
	int err;

	if (!tb[attrtype])
		return 0;

	if (nla_get_u8(tb[attrtype]))
		flags = p->flags | mask;
	else
		flags = p->flags & ~mask;

	err = br_switchdev_set_port_flag(p, flags, mask);
	if (err)
		return err;

	p->flags = flags;
	return 0;
}