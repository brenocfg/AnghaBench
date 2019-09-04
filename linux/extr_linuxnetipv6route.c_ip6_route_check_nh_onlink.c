#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {struct net_device const* dev; int /*<<< orphan*/  error; } ;
struct rt6_info {int rt6i_flags; TYPE_2__ dst; int /*<<< orphan*/  from; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct fib6_info {TYPE_1__ fib6_dst; } ;
struct fib6_config {struct in6_addr fc_gateway; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int RTF_ANYCAST ; 
 int RTF_LOCAL ; 
 int RTF_REJECT ; 
 int RT_TABLE_MAIN ; 
 struct rt6_info* ip6_nh_lookup_table (struct net*,struct fib6_config*,struct in6_addr const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_rt_put (struct rt6_info*) ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 
 scalar_t__ l3mdev_fib_table (struct net_device const*) ; 
 struct fib6_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int ip6_route_check_nh_onlink(struct net *net,
				     struct fib6_config *cfg,
				     const struct net_device *dev,
				     struct netlink_ext_ack *extack)
{
	u32 tbid = l3mdev_fib_table(dev) ? : RT_TABLE_MAIN;
	const struct in6_addr *gw_addr = &cfg->fc_gateway;
	u32 flags = RTF_LOCAL | RTF_ANYCAST | RTF_REJECT;
	struct fib6_info *from;
	struct rt6_info *grt;
	int err;

	err = 0;
	grt = ip6_nh_lookup_table(net, cfg, gw_addr, tbid, 0);
	if (grt) {
		rcu_read_lock();
		from = rcu_dereference(grt->from);
		if (!grt->dst.error &&
		    /* ignore match if it is the default route */
		    from && !ipv6_addr_any(&from->fib6_dst.addr) &&
		    (grt->rt6i_flags & flags || dev != grt->dst.dev)) {
			NL_SET_ERR_MSG(extack,
				       "Nexthop has invalid gateway or device mismatch");
			err = -EINVAL;
		}
		rcu_read_unlock();

		ip6_rt_put(grt);
	}

	return err;
}