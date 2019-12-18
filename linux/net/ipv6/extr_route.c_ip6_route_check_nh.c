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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct inet6_dev {int dummy; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {scalar_t__ flowi6_oif; struct in6_addr const daddr; } ;
struct fib6_result {int fib6_flags; TYPE_1__* nh; } ;
struct fib6_config {scalar_t__ fc_ifindex; int /*<<< orphan*/  fc_table; struct in6_addr fc_gateway; } ;
struct TYPE_2__ {struct net_device* fib_nh_dev; scalar_t__ fib_nh_gw_family; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int RT6_LOOKUP_F_IFACE ; 
 int RTF_REJECT ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int fib6_lookup (struct net*,scalar_t__,struct flowi6*,struct fib6_result*,int) ; 
 int /*<<< orphan*/  fib6_select_path (struct net*,struct fib6_result*,struct flowi6*,scalar_t__,int,int /*<<< orphan*/ *,int) ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int ip6_nh_lookup_table (struct net*,struct fib6_config*,struct in6_addr const*,int /*<<< orphan*/ ,int,struct fib6_result*) ; 

__attribute__((used)) static int ip6_route_check_nh(struct net *net,
			      struct fib6_config *cfg,
			      struct net_device **_dev,
			      struct inet6_dev **idev)
{
	const struct in6_addr *gw_addr = &cfg->fc_gateway;
	struct net_device *dev = _dev ? *_dev : NULL;
	int flags = RT6_LOOKUP_F_IFACE;
	struct fib6_result res = {};
	int err = -EHOSTUNREACH;

	if (cfg->fc_table) {
		err = ip6_nh_lookup_table(net, cfg, gw_addr,
					  cfg->fc_table, flags, &res);
		/* gw_addr can not require a gateway or resolve to a reject
		 * route. If a device is given, it must match the result.
		 */
		if (err || res.fib6_flags & RTF_REJECT ||
		    res.nh->fib_nh_gw_family ||
		    (dev && dev != res.nh->fib_nh_dev))
			err = -EHOSTUNREACH;
	}

	if (err < 0) {
		struct flowi6 fl6 = {
			.flowi6_oif = cfg->fc_ifindex,
			.daddr = *gw_addr,
		};

		err = fib6_lookup(net, cfg->fc_ifindex, &fl6, &res, flags);
		if (err || res.fib6_flags & RTF_REJECT ||
		    res.nh->fib_nh_gw_family)
			err = -EHOSTUNREACH;

		if (err)
			return err;

		fib6_select_path(net, &res, &fl6, cfg->fc_ifindex,
				 cfg->fc_ifindex != 0, NULL, flags);
	}

	err = 0;
	if (dev) {
		if (dev != res.nh->fib_nh_dev)
			err = -EHOSTUNREACH;
	} else {
		*_dev = dev = res.nh->fib_nh_dev;
		dev_hold(dev);
		*idev = in6_dev_get(dev);
	}

	return err;
}