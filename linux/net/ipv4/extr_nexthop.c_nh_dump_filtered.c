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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {struct net_device* nhc_dev; } ;
struct nh_info {scalar_t__ family; TYPE_1__ fib_nhc; } ;
struct nexthop {int /*<<< orphan*/  nh_info; scalar_t__ is_group; } ;
struct net_device {int ifindex; } ;

/* Variables and functions */
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 
 struct nh_info* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nh_dump_filtered(struct nexthop *nh, int dev_idx, int master_idx,
			     bool group_filter, u8 family)
{
	const struct net_device *dev;
	const struct nh_info *nhi;

	if (group_filter && !nh->is_group)
		return true;

	if (!dev_idx && !master_idx && !family)
		return false;

	if (nh->is_group)
		return true;

	nhi = rtnl_dereference(nh->nh_info);
	if (family && nhi->family != family)
		return true;

	dev = nhi->fib_nhc.nhc_dev;
	if (dev_idx && (!dev || dev->ifindex != dev_idx))
		return true;

	if (master_idx) {
		struct net_device *master;

		if (!dev)
			return true;

		master = netdev_master_upper_dev_get((struct net_device *)dev);
		if (!master || master->ifindex != master_idx)
			return true;
	}

	return false;
}