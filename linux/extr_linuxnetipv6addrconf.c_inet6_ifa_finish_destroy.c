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
struct inet6_ifaddr {scalar_t__ state; int /*<<< orphan*/  dad_work; int /*<<< orphan*/  idev; int /*<<< orphan*/  addr_lst; } ;

/* Variables and functions */
 scalar_t__ INET6_IFADDR_STATE_DEAD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct inet6_ifaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  pr_warn (char*,struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  rcu ; 

void inet6_ifa_finish_destroy(struct inet6_ifaddr *ifp)
{
	WARN_ON(!hlist_unhashed(&ifp->addr_lst));

#ifdef NET_REFCNT_DEBUG
	pr_debug("%s\n", __func__);
#endif

	in6_dev_put(ifp->idev);

	if (cancel_delayed_work(&ifp->dad_work))
		pr_notice("delayed DAD work was pending while freeing ifa=%p\n",
			  ifp);

	if (ifp->state != INET6_IFADDR_STATE_DEAD) {
		pr_warn("Freeing alive inet6 address %p\n", ifp);
		return;
	}

	kfree_rcu(ifp, rcu);
}