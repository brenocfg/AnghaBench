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
struct TYPE_2__ {struct net_device* dev; } ;
struct rt6_info {int rt6i_flags; struct inet6_dev* rt6i_idev; TYPE_1__ dst; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct inet6_dev {int dummy; } ;
struct in6_addr {int dummy; } ;
struct fib6_config {int /*<<< orphan*/  fc_ifindex; int /*<<< orphan*/  fc_table; struct in6_addr fc_gateway; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int RT6_LOOKUP_F_IFACE ; 
 int RTF_GATEWAY ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_hold (struct inet6_dev*) ; 
 struct rt6_info* ip6_nh_lookup_table (struct net*,struct fib6_config*,struct in6_addr const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ip6_rt_put (struct rt6_info*) ; 
 struct rt6_info* rt6_lookup (struct net*,struct in6_addr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ip6_route_check_nh(struct net *net,
			      struct fib6_config *cfg,
			      struct net_device **_dev,
			      struct inet6_dev **idev)
{
	const struct in6_addr *gw_addr = &cfg->fc_gateway;
	struct net_device *dev = _dev ? *_dev : NULL;
	struct rt6_info *grt = NULL;
	int err = -EHOSTUNREACH;

	if (cfg->fc_table) {
		int flags = RT6_LOOKUP_F_IFACE;

		grt = ip6_nh_lookup_table(net, cfg, gw_addr,
					  cfg->fc_table, flags);
		if (grt) {
			if (grt->rt6i_flags & RTF_GATEWAY ||
			    (dev && dev != grt->dst.dev)) {
				ip6_rt_put(grt);
				grt = NULL;
			}
		}
	}

	if (!grt)
		grt = rt6_lookup(net, gw_addr, NULL, cfg->fc_ifindex, NULL, 1);

	if (!grt)
		goto out;

	if (dev) {
		if (dev != grt->dst.dev) {
			ip6_rt_put(grt);
			goto out;
		}
	} else {
		*_dev = dev = grt->dst.dev;
		*idev = grt->rt6i_idev;
		dev_hold(dev);
		in6_dev_hold(grt->rt6i_idev);
	}

	if (!(grt->rt6i_flags & RTF_GATEWAY))
		err = 0;

	ip6_rt_put(grt);

out:
	return err;
}