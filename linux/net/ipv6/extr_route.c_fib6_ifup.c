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
struct TYPE_3__ {struct fib6_info* fib6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct fib6_info {TYPE_2__* fib6_nh; int /*<<< orphan*/  nh; } ;
struct arg_netdev_event {scalar_t__ dev; int /*<<< orphan*/  nh_flags; } ;
struct TYPE_4__ {scalar_t__ fib_nh_dev; int /*<<< orphan*/  fib_nh_flags; } ;

/* Variables and functions */
 struct net* dev_net (scalar_t__) ; 
 int /*<<< orphan*/  fib6_update_sernum_upto_root (struct net*,struct fib6_info*) ; 
 int /*<<< orphan*/  rt6_multipath_rebalance (struct fib6_info*) ; 

__attribute__((used)) static int fib6_ifup(struct fib6_info *rt, void *p_arg)
{
	const struct arg_netdev_event *arg = p_arg;
	struct net *net = dev_net(arg->dev);

	if (rt != net->ipv6.fib6_null_entry && !rt->nh &&
	    rt->fib6_nh->fib_nh_dev == arg->dev) {
		rt->fib6_nh->fib_nh_flags &= ~arg->nh_flags;
		fib6_update_sernum_upto_root(net, rt);
		rt6_multipath_rebalance(rt);
	}

	return 0;
}