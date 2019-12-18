#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct fib6_result {int fib6_flags; scalar_t__ fib6_type; TYPE_3__* nh; TYPE_2__* f6i; } ;
struct fib6_config {struct in6_addr fc_gateway; } ;
struct TYPE_6__ {struct net_device const* fib_nh_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__ fib6_dst; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int RTF_REJECT ; 
 scalar_t__ RTN_UNICAST ; 
 int /*<<< orphan*/  RT_TABLE_MAIN ; 
 int ip6_nh_lookup_table (struct net*,struct fib6_config*,struct in6_addr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fib6_result*) ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 
 scalar_t__ l3mdev_fib_table_rcu (struct net_device const*) ; 

__attribute__((used)) static int ip6_route_check_nh_onlink(struct net *net,
				     struct fib6_config *cfg,
				     const struct net_device *dev,
				     struct netlink_ext_ack *extack)
{
	u32 tbid = l3mdev_fib_table_rcu(dev) ? : RT_TABLE_MAIN;
	const struct in6_addr *gw_addr = &cfg->fc_gateway;
	struct fib6_result res = {};
	int err;

	err = ip6_nh_lookup_table(net, cfg, gw_addr, tbid, 0, &res);
	if (!err && !(res.fib6_flags & RTF_REJECT) &&
	    /* ignore match if it is the default route */
	    !ipv6_addr_any(&res.f6i->fib6_dst.addr) &&
	    (res.fib6_type != RTN_UNICAST || dev != res.nh->fib_nh_dev)) {
		NL_SET_ERR_MSG(extack,
			       "Nexthop has invalid gateway or device mismatch");
		err = -EINVAL;
	}

	return err;
}