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
struct TYPE_3__ {scalar_t__ plen; } ;
struct rt6_info {TYPE_1__ rt6i_dst; TYPE_2__* rt6i_idev; } ;
struct net_device {scalar_t__ group; } ;
struct fib_rule {scalar_t__ suppress_prefixlen; int suppress_ifgroup; } ;
struct fib_lookup_arg {int flags; struct fib6_result* result; } ;
struct fib6_result {struct rt6_info* rt6; } ;
struct TYPE_4__ {struct net_device* dev; } ;

/* Variables and functions */
 int FIB_LOOKUP_NOREF ; 
 int /*<<< orphan*/  ip6_rt_put (struct rt6_info*) ; 

__attribute__((used)) static bool fib6_rule_suppress(struct fib_rule *rule, struct fib_lookup_arg *arg)
{
	struct fib6_result *res = arg->result;
	struct rt6_info *rt = res->rt6;
	struct net_device *dev = NULL;

	if (!rt)
		return false;

	if (rt->rt6i_idev)
		dev = rt->rt6i_idev->dev;

	/* do not accept result if the route does
	 * not meet the required prefix length
	 */
	if (rt->rt6i_dst.plen <= rule->suppress_prefixlen)
		goto suppress_route;

	/* do not accept result if the route uses a device
	 * belonging to a forbidden interface group
	 */
	if (rule->suppress_ifgroup != -1 && dev && dev->group == rule->suppress_ifgroup)
		goto suppress_route;

	return false;

suppress_route:
	if (!(arg->flags & FIB_LOOKUP_NOREF))
		ip6_rt_put(rt);
	return true;
}