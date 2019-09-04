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
struct rt6_info {int /*<<< orphan*/  rt6i_prefsrc; int /*<<< orphan*/  rt6i_flags; int /*<<< orphan*/  rt6i_gateway; int /*<<< orphan*/ * rt6i_idev; int /*<<< orphan*/  rt6i_dst; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nh_gw; } ;
struct fib6_info {int /*<<< orphan*/  fib6_prefsrc; int /*<<< orphan*/  fib6_flags; TYPE_1__ fib6_nh; int /*<<< orphan*/  fib6_dst; } ;

/* Variables and functions */
 struct net_device* fib6_info_nh_dev (struct fib6_info*) ; 
 int /*<<< orphan*/ * in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  ip6_rt_init_dst (struct rt6_info*,struct fib6_info*) ; 
 int /*<<< orphan*/  rt6_set_from (struct rt6_info*,struct fib6_info*) ; 

__attribute__((used)) static void ip6_rt_copy_init(struct rt6_info *rt, struct fib6_info *ort)
{
	struct net_device *dev = fib6_info_nh_dev(ort);

	ip6_rt_init_dst(rt, ort);

	rt->rt6i_dst = ort->fib6_dst;
	rt->rt6i_idev = dev ? in6_dev_get(dev) : NULL;
	rt->rt6i_gateway = ort->fib6_nh.nh_gw;
	rt->rt6i_flags = ort->fib6_flags;
	rt6_set_from(rt, ort);
#ifdef CONFIG_IPV6_SUBTREES
	rt->rt6i_src = ort->fib6_src;
#endif
	rt->rt6i_prefsrc = ort->fib6_prefsrc;
}