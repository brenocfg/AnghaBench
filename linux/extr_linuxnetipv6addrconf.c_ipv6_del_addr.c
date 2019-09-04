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
struct inet6_ifaddr {int state; int flags; TYPE_1__* idev; int /*<<< orphan*/  if_list; struct inet6_ifaddr* ifpub; int /*<<< orphan*/  tmp_list; int /*<<< orphan*/  addr_lst; int /*<<< orphan*/  lock; } ;
typedef  enum cleanup_prefix_rt_t { ____Placeholder_cleanup_prefix_rt_t } cleanup_prefix_rt_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int CLEANUP_PREFIX_RT_DEL ; 
 int CLEANUP_PREFIX_RT_NOP ; 
 int IFA_F_NOPREFIXROUTE ; 
 int IFA_F_PERMANENT ; 
 int IFA_F_TEMPORARY ; 
 int INET6_IFADDR_STATE_DEAD ; 
 int /*<<< orphan*/  NETDEV_DOWN ; 
 int /*<<< orphan*/  RTM_DELADDR ; 
 int /*<<< orphan*/  __in6_ifa_put (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_del_dad_work (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_hash_lock ; 
 int check_cleanup_prefix_route (struct inet6_ifaddr*,unsigned long*) ; 
 int /*<<< orphan*/  cleanup_prefix_route (struct inet6_ifaddr*,unsigned long,int) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  inet6addr_notifier_call_chain (int /*<<< orphan*/ ,struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  ipv6_ifa_notify (int /*<<< orphan*/ ,struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt6_remove_prefsrc (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipv6_del_addr(struct inet6_ifaddr *ifp)
{
	int state;
	enum cleanup_prefix_rt_t action = CLEANUP_PREFIX_RT_NOP;
	unsigned long expires;

	ASSERT_RTNL();

	spin_lock_bh(&ifp->lock);
	state = ifp->state;
	ifp->state = INET6_IFADDR_STATE_DEAD;
	spin_unlock_bh(&ifp->lock);

	if (state == INET6_IFADDR_STATE_DEAD)
		goto out;

	spin_lock_bh(&addrconf_hash_lock);
	hlist_del_init_rcu(&ifp->addr_lst);
	spin_unlock_bh(&addrconf_hash_lock);

	write_lock_bh(&ifp->idev->lock);

	if (ifp->flags&IFA_F_TEMPORARY) {
		list_del(&ifp->tmp_list);
		if (ifp->ifpub) {
			in6_ifa_put(ifp->ifpub);
			ifp->ifpub = NULL;
		}
		__in6_ifa_put(ifp);
	}

	if (ifp->flags & IFA_F_PERMANENT && !(ifp->flags & IFA_F_NOPREFIXROUTE))
		action = check_cleanup_prefix_route(ifp, &expires);

	list_del_rcu(&ifp->if_list);
	__in6_ifa_put(ifp);

	write_unlock_bh(&ifp->idev->lock);

	addrconf_del_dad_work(ifp);

	ipv6_ifa_notify(RTM_DELADDR, ifp);

	inet6addr_notifier_call_chain(NETDEV_DOWN, ifp);

	if (action != CLEANUP_PREFIX_RT_NOP) {
		cleanup_prefix_route(ifp, expires,
			action == CLEANUP_PREFIX_RT_DEL);
	}

	/* clean up prefsrc entries */
	rt6_remove_prefsrc(ifp);
out:
	in6_ifa_put(ifp);
}