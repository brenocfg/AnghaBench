#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dev_addr_genid; } ;
struct net {TYPE_2__ ipv6; } ;
struct inet6_ifaddr {struct fib6_info* rt; TYPE_5__* idev; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  addr; } ;
struct fib6_info {int /*<<< orphan*/  fib6_node; } ;
struct TYPE_7__ {int /*<<< orphan*/  forwarding; } ;
struct TYPE_10__ {TYPE_3__* dev; TYPE_1__ cnf; } ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_UP ; 
#define  RTM_DELADDR 129 
#define  RTM_NEWADDR 128 
 struct fib6_info* addrconf_get_prefix_route (int /*<<< orphan*/ *,int,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  addrconf_join_anycast (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_leave_anycast (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_leave_solict (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addrconf_prefix_route (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct net* dev_net (TYPE_3__*) ; 
 int /*<<< orphan*/  inet6_ifa_notify (int,struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  ip6_del_rt (struct net*,struct fib6_info*) ; 
 int /*<<< orphan*/  ip6_ins_rt (struct net*,struct fib6_info*) ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_genid_bump_ipv6 (struct net*) ; 

__attribute__((used)) static void __ipv6_ifa_notify(int event, struct inet6_ifaddr *ifp)
{
	struct net *net = dev_net(ifp->idev->dev);

	if (event)
		ASSERT_RTNL();

	inet6_ifa_notify(event ? : RTM_NEWADDR, ifp);

	switch (event) {
	case RTM_NEWADDR:
		/*
		 * If the address was optimistic we inserted the route at the
		 * start of our DAD process, so we don't need to do it again.
		 * If the device was taken down in the middle of the DAD
		 * cycle there is a race where we could get here without a
		 * host route, so nothing to insert. That will be fixed when
		 * the device is brought up.
		 */
		if (ifp->rt && !rcu_access_pointer(ifp->rt->fib6_node)) {
			ip6_ins_rt(net, ifp->rt);
		} else if (!ifp->rt && (ifp->idev->dev->flags & IFF_UP)) {
			pr_warn("BUG: Address %pI6c on device %s is missing its host route.\n",
				&ifp->addr, ifp->idev->dev->name);
		}

		if (ifp->idev->cnf.forwarding)
			addrconf_join_anycast(ifp);
		if (!ipv6_addr_any(&ifp->peer_addr))
			addrconf_prefix_route(&ifp->peer_addr, 128, 0,
					      ifp->idev->dev, 0, 0,
					      GFP_ATOMIC);
		break;
	case RTM_DELADDR:
		if (ifp->idev->cnf.forwarding)
			addrconf_leave_anycast(ifp);
		addrconf_leave_solict(ifp->idev, &ifp->addr);
		if (!ipv6_addr_any(&ifp->peer_addr)) {
			struct fib6_info *rt;

			rt = addrconf_get_prefix_route(&ifp->peer_addr, 128,
						       ifp->idev->dev, 0, 0,
						       false);
			if (rt)
				ip6_del_rt(net, rt);
		}
		if (ifp->rt) {
			ip6_del_rt(net, ifp->rt);
			ifp->rt = NULL;
		}
		rt_genid_bump_ipv6(net);
		break;
	}
	atomic_inc(&net->ipv6.dev_addr_genid);
}