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
typedef  scalar_t__ u32 ;
struct inet6_ifaddr {TYPE_1__* idev; scalar_t__ rt_priority; int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; } ;
struct fib6_info {scalar_t__ fib6_metric; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IP6_RT_PRIO_ADDRCONF ; 
 int /*<<< orphan*/  RTF_DEFAULT ; 
 struct fib6_info* addrconf_get_prefix_route (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  addrconf_prefix_route (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned long,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib6_clean_expires (struct fib6_info*) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 int /*<<< orphan*/  fib6_set_expires (struct fib6_info*,unsigned long) ; 
 int /*<<< orphan*/  ip6_del_rt (int /*<<< orphan*/ ,struct fib6_info*) ; 

__attribute__((used)) static int modify_prefix_route(struct inet6_ifaddr *ifp,
			       unsigned long expires, u32 flags)
{
	struct fib6_info *f6i;
	u32 prio;

	f6i = addrconf_get_prefix_route(&ifp->addr, ifp->prefix_len,
					ifp->idev->dev, 0, RTF_DEFAULT, true);
	if (!f6i)
		return -ENOENT;

	prio = ifp->rt_priority ? : IP6_RT_PRIO_ADDRCONF;
	if (f6i->fib6_metric != prio) {
		/* delete old one */
		ip6_del_rt(dev_net(ifp->idev->dev), f6i);

		/* add new one */
		addrconf_prefix_route(&ifp->addr, ifp->prefix_len,
				      ifp->rt_priority, ifp->idev->dev,
				      expires, flags, GFP_KERNEL);
	} else {
		if (!expires)
			fib6_clean_expires(f6i);
		else
			fib6_set_expires(f6i, expires);

		fib6_info_release(f6i);
	}

	return 0;
}