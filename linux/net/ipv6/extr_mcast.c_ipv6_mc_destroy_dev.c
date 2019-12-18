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
struct TYPE_2__ {scalar_t__ forwarding; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct ifmcaddr6* mc_list; TYPE_1__ cnf; } ;
struct ifmcaddr6 {struct ifmcaddr6* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipv6_dev_mc_dec (struct inet6_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6addr_linklocal_allnodes ; 
 int /*<<< orphan*/  in6addr_linklocal_allrouters ; 
 int /*<<< orphan*/  ipv6_mc_down (struct inet6_dev*) ; 
 int /*<<< orphan*/  ma_put (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  mld_clear_delrec (struct inet6_dev*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void ipv6_mc_destroy_dev(struct inet6_dev *idev)
{
	struct ifmcaddr6 *i;

	/* Deactivate timers */
	ipv6_mc_down(idev);
	mld_clear_delrec(idev);

	/* Delete all-nodes address. */
	/* We cannot call ipv6_dev_mc_dec() directly, our caller in
	 * addrconf.c has NULL'd out dev->ip6_ptr so in6_dev_get() will
	 * fail.
	 */
	__ipv6_dev_mc_dec(idev, &in6addr_linklocal_allnodes);

	if (idev->cnf.forwarding)
		__ipv6_dev_mc_dec(idev, &in6addr_linklocal_allrouters);

	write_lock_bh(&idev->lock);
	while ((i = idev->mc_list) != NULL) {
		idev->mc_list = i->next;

		write_unlock_bh(&idev->lock);
		ma_put(i);
		write_lock_bh(&idev->lock);
	}
	write_unlock_bh(&idev->lock);
}