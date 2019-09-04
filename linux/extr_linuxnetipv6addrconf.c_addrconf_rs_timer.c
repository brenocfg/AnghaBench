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
struct timer_list {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ rtr_solicits; int /*<<< orphan*/  rtr_solicit_delay; int /*<<< orphan*/  rtr_solicit_max_interval; } ;
struct inet6_dev {int if_flags; scalar_t__ rs_probes; int /*<<< orphan*/  lock; struct net_device* dev; int /*<<< orphan*/  rs_interval; TYPE_1__ cnf; scalar_t__ dead; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_F_TENTATIVE ; 
 int IF_RA_RCVD ; 
 int IF_READY ; 
 int /*<<< orphan*/  addrconf_mod_rs_timer (struct inet6_dev*,int /*<<< orphan*/ ) ; 
 struct inet6_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct inet6_dev* idev ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  in6addr_linklocal_allrouters ; 
 int /*<<< orphan*/  ipv6_accept_ra (struct inet6_dev*) ; 
 int /*<<< orphan*/  ipv6_get_lladdr (struct net_device*,struct in6_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndisc_send_rs (struct net_device*,struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfc3315_s14_backoff_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_timer ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void addrconf_rs_timer(struct timer_list *t)
{
	struct inet6_dev *idev = from_timer(idev, t, rs_timer);
	struct net_device *dev = idev->dev;
	struct in6_addr lladdr;

	write_lock(&idev->lock);
	if (idev->dead || !(idev->if_flags & IF_READY))
		goto out;

	if (!ipv6_accept_ra(idev))
		goto out;

	/* Announcement received after solicitation was sent */
	if (idev->if_flags & IF_RA_RCVD)
		goto out;

	if (idev->rs_probes++ < idev->cnf.rtr_solicits || idev->cnf.rtr_solicits < 0) {
		write_unlock(&idev->lock);
		if (!ipv6_get_lladdr(dev, &lladdr, IFA_F_TENTATIVE))
			ndisc_send_rs(dev, &lladdr,
				      &in6addr_linklocal_allrouters);
		else
			goto put;

		write_lock(&idev->lock);
		idev->rs_interval = rfc3315_s14_backoff_update(
			idev->rs_interval, idev->cnf.rtr_solicit_max_interval);
		/* The wait after the last probe can be shorter */
		addrconf_mod_rs_timer(idev, (idev->rs_probes ==
					     idev->cnf.rtr_solicits) ?
				      idev->cnf.rtr_solicit_delay :
				      idev->rs_interval);
	} else {
		/*
		 * Note: we do not support deprecated "all on-link"
		 * assumption any longer.
		 */
		pr_debug("%s: no IPv6 routers present\n", idev->dev->name);
	}

out:
	write_unlock(&idev->lock);
put:
	in6_dev_put(idev);
}