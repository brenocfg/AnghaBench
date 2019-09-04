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
typedef  int u32 ;
struct inet6_ifaddr {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; } ;
struct inet6_dev {int /*<<< orphan*/  dev; } ;
struct in6_addr {int dummy; } ;
struct ifa6_config {int plen; int ifa_flags; int /*<<< orphan*/  scope; int /*<<< orphan*/  preferred_lft; int /*<<< orphan*/  valid_lft; struct in6_addr const* pfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFA_F_PERMANENT ; 
 int /*<<< orphan*/  IFA_LINK ; 
 int /*<<< orphan*/  INFINITY_LIFE_TIME ; 
 int /*<<< orphan*/  IS_ERR (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_dad_start (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_prefix_route (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 struct inet6_ifaddr* ipv6_add_addr (struct inet6_dev*,struct ifa6_config*,int,int /*<<< orphan*/ *) ; 

void addrconf_add_linklocal(struct inet6_dev *idev,
			    const struct in6_addr *addr, u32 flags)
{
	struct ifa6_config cfg = {
		.pfx = addr,
		.plen = 64,
		.ifa_flags = flags | IFA_F_PERMANENT,
		.valid_lft = INFINITY_LIFE_TIME,
		.preferred_lft = INFINITY_LIFE_TIME,
		.scope = IFA_LINK
	};
	struct inet6_ifaddr *ifp;

#ifdef CONFIG_IPV6_OPTIMISTIC_DAD
	if ((dev_net(idev->dev)->ipv6.devconf_all->optimistic_dad ||
	     idev->cnf.optimistic_dad) &&
	    !dev_net(idev->dev)->ipv6.devconf_all->forwarding)
		cfg.ifa_flags |= IFA_F_OPTIMISTIC;
#endif

	ifp = ipv6_add_addr(idev, &cfg, true, NULL);
	if (!IS_ERR(ifp)) {
		addrconf_prefix_route(&ifp->addr, ifp->prefix_len, 0, idev->dev,
				      0, 0, GFP_ATOMIC);
		addrconf_dad_start(ifp);
		in6_ifa_put(ifp);
	}
}