#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rt6_info {int /*<<< orphan*/  rt6i_src; int /*<<< orphan*/  rt6i_flags; int /*<<< orphan*/  rt6i_gateway; int /*<<< orphan*/ * rt6i_idev; int /*<<< orphan*/  rt6i_dst; } ;
struct net_device {int dummy; } ;
struct fib6_result {int /*<<< orphan*/  fib6_flags; struct fib6_info* f6i; struct fib6_nh* nh; } ;
struct fib6_nh {int /*<<< orphan*/  fib_nh_gw6; scalar_t__ fib_nh_gw_family; struct net_device* fib_nh_dev; } ;
struct fib6_info {int /*<<< orphan*/  fib6_src; int /*<<< orphan*/  fib6_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTF_GATEWAY ; 
 int /*<<< orphan*/ * in6_dev_get (struct net_device const*) ; 
 int /*<<< orphan*/  ip6_rt_init_dst (struct rt6_info*,struct fib6_result const*) ; 
 int /*<<< orphan*/  rt6_set_from (struct rt6_info*,struct fib6_info*) ; 

__attribute__((used)) static void ip6_rt_copy_init(struct rt6_info *rt, const struct fib6_result *res)
{
	const struct fib6_nh *nh = res->nh;
	const struct net_device *dev = nh->fib_nh_dev;
	struct fib6_info *f6i = res->f6i;

	ip6_rt_init_dst(rt, res);

	rt->rt6i_dst = f6i->fib6_dst;
	rt->rt6i_idev = dev ? in6_dev_get(dev) : NULL;
	rt->rt6i_flags = res->fib6_flags;
	if (nh->fib_nh_gw_family) {
		rt->rt6i_gateway = nh->fib_nh_gw6;
		rt->rt6i_flags |= RTF_GATEWAY;
	}
	rt6_set_from(rt, f6i);
#ifdef CONFIG_IPV6_SUBTREES
	rt->rt6i_src = f6i->fib6_src;
#endif
}