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
struct inet6_ifaddr {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct inet6_dev {int /*<<< orphan*/  dev; } ;
struct in6_addr {int dummy; } ;
struct ifa6_config {int plen; int scope; int /*<<< orphan*/  preferred_lft; int /*<<< orphan*/  valid_lft; int /*<<< orphan*/  ifa_flags; struct in6_addr const* pfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_F_PERMANENT ; 
 int /*<<< orphan*/  IFA_F_TENTATIVE ; 
 int /*<<< orphan*/  INFINITY_LIFE_TIME ; 
 int /*<<< orphan*/  IS_ERR (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  RTM_NEWADDR ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 struct inet6_ifaddr* ipv6_add_addr (struct inet6_dev*,struct ifa6_config*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_ifa_notify (int /*<<< orphan*/ ,struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  rt_genid_bump_ipv6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_addr(struct inet6_dev *idev, const struct in6_addr *addr,
		     int plen, int scope)
{
	struct inet6_ifaddr *ifp;
	struct ifa6_config cfg = {
		.pfx = addr,
		.plen = plen,
		.ifa_flags = IFA_F_PERMANENT,
		.valid_lft = INFINITY_LIFE_TIME,
		.preferred_lft = INFINITY_LIFE_TIME,
		.scope = scope
	};

	ifp = ipv6_add_addr(idev, &cfg, true, NULL);
	if (!IS_ERR(ifp)) {
		spin_lock_bh(&ifp->lock);
		ifp->flags &= ~IFA_F_TENTATIVE;
		spin_unlock_bh(&ifp->lock);
		rt_genid_bump_ipv6(dev_net(idev->dev));
		ipv6_ifa_notify(RTM_NEWADDR, ifp);
		in6_ifa_put(ifp);
	}
}