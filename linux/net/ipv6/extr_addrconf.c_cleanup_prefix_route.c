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
struct inet6_ifaddr {TYPE_1__* idev; int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; } ;
struct fib6_info {int fib6_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTF_DEFAULT ; 
 int RTF_EXPIRES ; 
 struct fib6_info* addrconf_get_prefix_route (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 int /*<<< orphan*/  fib6_set_expires (struct fib6_info*,unsigned long) ; 
 int /*<<< orphan*/  ip6_del_rt (int /*<<< orphan*/ ,struct fib6_info*) ; 

__attribute__((used)) static void
cleanup_prefix_route(struct inet6_ifaddr *ifp, unsigned long expires, bool del_rt)
{
	struct fib6_info *f6i;

	f6i = addrconf_get_prefix_route(&ifp->addr, ifp->prefix_len,
					ifp->idev->dev, 0, RTF_DEFAULT, true);
	if (f6i) {
		if (del_rt)
			ip6_del_rt(dev_net(ifp->idev->dev), f6i);
		else {
			if (!(f6i->fib6_flags & RTF_EXPIRES))
				fib6_set_expires(f6i, expires);
			fib6_info_release(f6i);
		}
	}
}