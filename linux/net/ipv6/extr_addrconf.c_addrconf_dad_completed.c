#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; } ;
struct inet6_ifaddr {scalar_t__ scope; int flags; TYPE_5__* idev; int /*<<< orphan*/  lock; int /*<<< orphan*/  addr; } ;
struct in6_addr {int dummy; } ;
struct TYPE_11__ {scalar_t__ rtr_solicits; int /*<<< orphan*/  rtr_solicit_interval; int /*<<< orphan*/  forwarding; scalar_t__ ndisc_notify; } ;
struct TYPE_13__ {int rs_probes; int /*<<< orphan*/  lock; int /*<<< orphan*/  rs_interval; int /*<<< orphan*/  if_flags; TYPE_3__ cnf; struct net_device* dev; } ;
struct TYPE_10__ {TYPE_1__* devconf_all; } ;
struct TYPE_12__ {TYPE_2__ ipv6; } ;
struct TYPE_9__ {scalar_t__ ndisc_notify; } ;

/* Variables and functions */
 int IFA_F_TEMPORARY ; 
 int /*<<< orphan*/  IFA_F_TENTATIVE ; 
 scalar_t__ IFA_LINK ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  IF_RS_SENT ; 
 int /*<<< orphan*/  RTM_NEWADDR ; 
 int /*<<< orphan*/  addrconf_del_dad_work (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_mod_rs_timer (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addrconf_verify_rtnl () ; 
 TYPE_4__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  in6addr_linklocal_allnodes ; 
 int /*<<< orphan*/  in6addr_linklocal_allrouters ; 
 scalar_t__ ipv6_accept_ra (TYPE_5__*) ; 
 scalar_t__ ipv6_get_lladdr (struct net_device*,struct in6_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_ifa_notify (int /*<<< orphan*/ ,struct inet6_ifaddr*) ; 
 scalar_t__ ipv6_lonely_lladdr (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  ipv6_mc_dad_complete (TYPE_5__*) ; 
 int /*<<< orphan*/  ndisc_send_na (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  ndisc_send_rs (struct net_device*,struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfc3315_s14_backoff_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_genid_bump_ipv6 (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void addrconf_dad_completed(struct inet6_ifaddr *ifp, bool bump_id,
				   bool send_na)
{
	struct net_device *dev = ifp->idev->dev;
	struct in6_addr lladdr;
	bool send_rs, send_mld;

	addrconf_del_dad_work(ifp);

	/*
	 *	Configure the address for reception. Now it is valid.
	 */

	ipv6_ifa_notify(RTM_NEWADDR, ifp);

	/* If added prefix is link local and we are prepared to process
	   router advertisements, start sending router solicitations.
	 */

	read_lock_bh(&ifp->idev->lock);
	send_mld = ifp->scope == IFA_LINK && ipv6_lonely_lladdr(ifp);
	send_rs = send_mld &&
		  ipv6_accept_ra(ifp->idev) &&
		  ifp->idev->cnf.rtr_solicits != 0 &&
		  (dev->flags&IFF_LOOPBACK) == 0;
	read_unlock_bh(&ifp->idev->lock);

	/* While dad is in progress mld report's source address is in6_addrany.
	 * Resend with proper ll now.
	 */
	if (send_mld)
		ipv6_mc_dad_complete(ifp->idev);

	/* send unsolicited NA if enabled */
	if (send_na &&
	    (ifp->idev->cnf.ndisc_notify ||
	     dev_net(dev)->ipv6.devconf_all->ndisc_notify)) {
		ndisc_send_na(dev, &in6addr_linklocal_allnodes, &ifp->addr,
			      /*router=*/ !!ifp->idev->cnf.forwarding,
			      /*solicited=*/ false, /*override=*/ true,
			      /*inc_opt=*/ true);
	}

	if (send_rs) {
		/*
		 *	If a host as already performed a random delay
		 *	[...] as part of DAD [...] there is no need
		 *	to delay again before sending the first RS
		 */
		if (ipv6_get_lladdr(dev, &lladdr, IFA_F_TENTATIVE))
			return;
		ndisc_send_rs(dev, &lladdr, &in6addr_linklocal_allrouters);

		write_lock_bh(&ifp->idev->lock);
		spin_lock(&ifp->lock);
		ifp->idev->rs_interval = rfc3315_s14_backoff_init(
			ifp->idev->cnf.rtr_solicit_interval);
		ifp->idev->rs_probes = 1;
		ifp->idev->if_flags |= IF_RS_SENT;
		addrconf_mod_rs_timer(ifp->idev, ifp->idev->rs_interval);
		spin_unlock(&ifp->lock);
		write_unlock_bh(&ifp->idev->lock);
	}

	if (bump_id)
		rt_genid_bump_ipv6(dev_net(dev));

	/* Make sure that a new temporary address will be created
	 * before this temporary address becomes deprecated.
	 */
	if (ifp->flags & IFA_F_TEMPORARY)
		addrconf_verify_rtnl();
}