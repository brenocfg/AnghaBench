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
struct net_device {int dummy; } ;
struct TYPE_3__ {struct fib6_info* fib6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct fib6_info {int fib6_flags; TYPE_2__* fib6_nh; int /*<<< orphan*/  fib6_nsiblings; int /*<<< orphan*/  should_flush; scalar_t__ nh; } ;
struct arg_netdev_event {int event; struct net_device* dev; } ;
struct TYPE_4__ {int fib_nh_flags; struct net_device const* fib_nh_dev; } ;

/* Variables and functions */
#define  NETDEV_CHANGE 130 
#define  NETDEV_DOWN 129 
#define  NETDEV_UNREGISTER 128 
 int RTF_ANYCAST ; 
 int RTF_LOCAL ; 
 int RTNH_F_DEAD ; 
 int RTNH_F_LINKDOWN ; 
 struct net* dev_net (struct net_device const*) ; 
 int /*<<< orphan*/  fib6_update_sernum (struct net*,struct fib6_info*) ; 
 unsigned int rt6_multipath_dead_count (struct fib6_info*,struct net_device const*) ; 
 int /*<<< orphan*/  rt6_multipath_flush (struct fib6_info*) ; 
 int /*<<< orphan*/  rt6_multipath_nh_flags_set (struct fib6_info*,struct net_device const*,int) ; 
 int /*<<< orphan*/  rt6_multipath_rebalance (struct fib6_info*) ; 
 int /*<<< orphan*/  rt6_multipath_uses_dev (struct fib6_info*,struct net_device const*) ; 

__attribute__((used)) static int fib6_ifdown(struct fib6_info *rt, void *p_arg)
{
	const struct arg_netdev_event *arg = p_arg;
	const struct net_device *dev = arg->dev;
	struct net *net = dev_net(dev);

	if (rt == net->ipv6.fib6_null_entry || rt->nh)
		return 0;

	switch (arg->event) {
	case NETDEV_UNREGISTER:
		return rt->fib6_nh->fib_nh_dev == dev ? -1 : 0;
	case NETDEV_DOWN:
		if (rt->should_flush)
			return -1;
		if (!rt->fib6_nsiblings)
			return rt->fib6_nh->fib_nh_dev == dev ? -1 : 0;
		if (rt6_multipath_uses_dev(rt, dev)) {
			unsigned int count;

			count = rt6_multipath_dead_count(rt, dev);
			if (rt->fib6_nsiblings + 1 == count) {
				rt6_multipath_flush(rt);
				return -1;
			}
			rt6_multipath_nh_flags_set(rt, dev, RTNH_F_DEAD |
						   RTNH_F_LINKDOWN);
			fib6_update_sernum(net, rt);
			rt6_multipath_rebalance(rt);
		}
		return -2;
	case NETDEV_CHANGE:
		if (rt->fib6_nh->fib_nh_dev != dev ||
		    rt->fib6_flags & (RTF_LOCAL | RTF_ANYCAST))
			break;
		rt->fib6_nh->fib_nh_flags |= RTNH_F_LINKDOWN;
		rt6_multipath_rebalance(rt);
		break;
	}

	return 0;
}