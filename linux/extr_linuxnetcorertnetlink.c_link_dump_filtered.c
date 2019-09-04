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
struct rtnl_link_ops {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ link_kind_filtered (struct net_device*,struct rtnl_link_ops const*) ; 
 scalar_t__ link_master_filtered (struct net_device*,int) ; 

__attribute__((used)) static bool link_dump_filtered(struct net_device *dev,
			       int master_idx,
			       const struct rtnl_link_ops *kind_ops)
{
	if (link_master_filtered(dev, master_idx) ||
	    link_kind_filtered(dev, kind_ops))
		return true;

	return false;
}