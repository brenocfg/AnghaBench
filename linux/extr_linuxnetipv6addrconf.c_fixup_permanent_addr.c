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
struct net {int dummy; } ;
struct inet6_ifaddr {int flags; scalar_t__ state; int /*<<< orphan*/  rt_priority; int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; int /*<<< orphan*/  lock; struct fib6_info* rt; } ;
struct inet6_dev {int /*<<< orphan*/  dev; } ;
struct fib6_info {int /*<<< orphan*/  fib6_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFA_F_NOPREFIXROUTE ; 
 scalar_t__ INET6_IFADDR_STATE_PREDAD ; 
 scalar_t__ IS_ERR (struct fib6_info*) ; 
 int PTR_ERR (struct fib6_info*) ; 
 int /*<<< orphan*/  addrconf_dad_start (struct inet6_ifaddr*) ; 
 struct fib6_info* addrconf_f6i_alloc (struct net*,struct inet6_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addrconf_prefix_route (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fixup_permanent_addr(struct net *net,
				struct inet6_dev *idev,
				struct inet6_ifaddr *ifp)
{
	/* !fib6_node means the host route was removed from the
	 * FIB, for example, if 'lo' device is taken down. In that
	 * case regenerate the host route.
	 */
	if (!ifp->rt || !ifp->rt->fib6_node) {
		struct fib6_info *f6i, *prev;

		f6i = addrconf_f6i_alloc(net, idev, &ifp->addr, false,
					 GFP_ATOMIC);
		if (IS_ERR(f6i))
			return PTR_ERR(f6i);

		/* ifp->rt can be accessed outside of rtnl */
		spin_lock(&ifp->lock);
		prev = ifp->rt;
		ifp->rt = f6i;
		spin_unlock(&ifp->lock);

		fib6_info_release(prev);
	}

	if (!(ifp->flags & IFA_F_NOPREFIXROUTE)) {
		addrconf_prefix_route(&ifp->addr, ifp->prefix_len,
				      ifp->rt_priority, idev->dev, 0, 0,
				      GFP_ATOMIC);
	}

	if (ifp->state == INET6_IFADDR_STATE_PREDAD)
		addrconf_dad_start(ifp);

	return 0;
}