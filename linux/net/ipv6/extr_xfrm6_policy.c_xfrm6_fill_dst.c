#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int rt6i_flags; int /*<<< orphan*/  rt6i_uncached; int /*<<< orphan*/  rt6i_src; int /*<<< orphan*/  rt6i_dst; int /*<<< orphan*/  rt6i_gateway; int /*<<< orphan*/  rt6i_idev; } ;
struct TYPE_7__ {struct net_device* dev; } ;
struct TYPE_8__ {TYPE_5__ rt6; TYPE_1__ dst; } ;
struct xfrm_dst {TYPE_2__ u; int /*<<< orphan*/  route_cookie; scalar_t__ route; } ;
struct rt6_info {int rt6i_flags; int /*<<< orphan*/  rt6i_src; int /*<<< orphan*/  rt6i_dst; int /*<<< orphan*/  rt6i_gateway; } ;
struct net_device {int dummy; } ;
struct flowi {int dummy; } ;
struct TYPE_10__ {TYPE_3__* rt6_stats; } ;
struct TYPE_12__ {TYPE_4__ ipv6; } ;
struct TYPE_9__ {int /*<<< orphan*/  fib_rt_uncache; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int RTF_ANYCAST ; 
 int RTF_LOCAL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 TYPE_6__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  rt6_get_cookie (struct rt6_info*) ; 
 int /*<<< orphan*/  rt6_uncached_list_add (TYPE_5__*) ; 

__attribute__((used)) static int xfrm6_fill_dst(struct xfrm_dst *xdst, struct net_device *dev,
			  const struct flowi *fl)
{
	struct rt6_info *rt = (struct rt6_info *)xdst->route;

	xdst->u.dst.dev = dev;
	dev_hold(dev);

	xdst->u.rt6.rt6i_idev = in6_dev_get(dev);
	if (!xdst->u.rt6.rt6i_idev) {
		dev_put(dev);
		return -ENODEV;
	}

	/* Sheit... I remember I did this right. Apparently,
	 * it was magically lost, so this code needs audit */
	xdst->u.rt6.rt6i_flags = rt->rt6i_flags & (RTF_ANYCAST |
						   RTF_LOCAL);
	xdst->route_cookie = rt6_get_cookie(rt);
	xdst->u.rt6.rt6i_gateway = rt->rt6i_gateway;
	xdst->u.rt6.rt6i_dst = rt->rt6i_dst;
	xdst->u.rt6.rt6i_src = rt->rt6i_src;
	INIT_LIST_HEAD(&xdst->u.rt6.rt6i_uncached);
	rt6_uncached_list_add(&xdst->u.rt6);
	atomic_inc(&dev_net(dev)->ipv6.rt6_stats->fib_rt_uncache);

	return 0;
}