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
struct net_device {TYPE_1__* netdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_has_offload_stats ) (struct net_device const*,int) ;scalar_t__ ndo_get_offload_stats; } ;

/* Variables and functions */
 int IFLA_OFFLOAD_XSTATS_FIRST ; 
 int IFLA_OFFLOAD_XSTATS_MAX ; 
 scalar_t__ nla_total_size (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_total_size_64bit (int) ; 
 int rtnl_get_offload_stats_attr_size (int) ; 
 int /*<<< orphan*/  stub1 (struct net_device const*,int) ; 

__attribute__((used)) static int rtnl_get_offload_stats_size(const struct net_device *dev)
{
	int nla_size = 0;
	int attr_id;
	int size;

	if (!(dev->netdev_ops && dev->netdev_ops->ndo_has_offload_stats &&
	      dev->netdev_ops->ndo_get_offload_stats))
		return 0;

	for (attr_id = IFLA_OFFLOAD_XSTATS_FIRST;
	     attr_id <= IFLA_OFFLOAD_XSTATS_MAX; attr_id++) {
		if (!dev->netdev_ops->ndo_has_offload_stats(dev, attr_id))
			continue;
		size = rtnl_get_offload_stats_attr_size(attr_id);
		nla_size += nla_total_size_64bit(size);
	}

	if (nla_size != 0)
		nla_size += nla_total_size(0);

	return nla_size;
}