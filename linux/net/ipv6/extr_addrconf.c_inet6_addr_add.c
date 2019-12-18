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
typedef  scalar_t__ u32 ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mc_autojoin_sk; } ;
struct net {TYPE_1__ ipv6; } ;
struct inet6_ifaddr {int flags; int /*<<< orphan*/  rt_priority; int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; } ;
struct inet6_dev {int flags; int /*<<< orphan*/  rt_priority; int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; } ;
struct ifa6_config {int plen; unsigned long valid_lft; unsigned long preferred_lft; int ifa_flags; int /*<<< orphan*/  pfx; int /*<<< orphan*/  scope; } ;
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long HZ ; 
 int IFA_F_DEPRECATED ; 
 int IFA_F_MANAGETEMPADDR ; 
 int IFA_F_MCAUTOJOIN ; 
 int IFA_F_NODAD ; 
 int IFA_F_NOPREFIXROUTE ; 
 int IFA_F_OPTIMISTIC ; 
 int IFA_F_PERMANENT ; 
 scalar_t__ IS_ERR (struct inet6_ifaddr*) ; 
 int PTR_ERR (struct inet6_ifaddr*) ; 
 scalar_t__ RTF_EXPIRES ; 
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 struct inet6_ifaddr* addrconf_add_dev (struct net_device*) ; 
 int /*<<< orphan*/  addrconf_dad_start (struct inet6_ifaddr*) ; 
 scalar_t__ addrconf_finite_timeout (unsigned long) ; 
 int /*<<< orphan*/  addrconf_prefix_route (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long addrconf_timeout_fixup (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  addrconf_verify_rtnl () ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 struct inet6_ifaddr* ipv6_add_addr (struct inet6_ifaddr*,struct ifa6_config*,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  ipv6_addr_scope (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_ifa_notify (int /*<<< orphan*/ ,struct inet6_ifaddr*) ; 
 int ipv6_mc_config (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ jiffies_to_clock_t (unsigned long) ; 
 int /*<<< orphan*/  manage_tempaddrs (struct inet6_ifaddr*,struct inet6_ifaddr*,unsigned long,unsigned long,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet6_addr_add(struct net *net, int ifindex,
			  struct ifa6_config *cfg,
			  struct netlink_ext_ack *extack)
{
	struct inet6_ifaddr *ifp;
	struct inet6_dev *idev;
	struct net_device *dev;
	unsigned long timeout;
	clock_t expires;
	u32 flags;

	ASSERT_RTNL();

	if (cfg->plen > 128)
		return -EINVAL;

	/* check the lifetime */
	if (!cfg->valid_lft || cfg->preferred_lft > cfg->valid_lft)
		return -EINVAL;

	if (cfg->ifa_flags & IFA_F_MANAGETEMPADDR && cfg->plen != 64)
		return -EINVAL;

	dev = __dev_get_by_index(net, ifindex);
	if (!dev)
		return -ENODEV;

	idev = addrconf_add_dev(dev);
	if (IS_ERR(idev))
		return PTR_ERR(idev);

	if (cfg->ifa_flags & IFA_F_MCAUTOJOIN) {
		int ret = ipv6_mc_config(net->ipv6.mc_autojoin_sk,
					 true, cfg->pfx, ifindex);

		if (ret < 0)
			return ret;
	}

	cfg->scope = ipv6_addr_scope(cfg->pfx);

	timeout = addrconf_timeout_fixup(cfg->valid_lft, HZ);
	if (addrconf_finite_timeout(timeout)) {
		expires = jiffies_to_clock_t(timeout * HZ);
		cfg->valid_lft = timeout;
		flags = RTF_EXPIRES;
	} else {
		expires = 0;
		flags = 0;
		cfg->ifa_flags |= IFA_F_PERMANENT;
	}

	timeout = addrconf_timeout_fixup(cfg->preferred_lft, HZ);
	if (addrconf_finite_timeout(timeout)) {
		if (timeout == 0)
			cfg->ifa_flags |= IFA_F_DEPRECATED;
		cfg->preferred_lft = timeout;
	}

	ifp = ipv6_add_addr(idev, cfg, true, extack);
	if (!IS_ERR(ifp)) {
		if (!(cfg->ifa_flags & IFA_F_NOPREFIXROUTE)) {
			addrconf_prefix_route(&ifp->addr, ifp->prefix_len,
					      ifp->rt_priority, dev, expires,
					      flags, GFP_KERNEL);
		}

		/* Send a netlink notification if DAD is enabled and
		 * optimistic flag is not set
		 */
		if (!(ifp->flags & (IFA_F_OPTIMISTIC | IFA_F_NODAD)))
			ipv6_ifa_notify(0, ifp);
		/*
		 * Note that section 3.1 of RFC 4429 indicates
		 * that the Optimistic flag should not be set for
		 * manually configured addresses
		 */
		addrconf_dad_start(ifp);
		if (cfg->ifa_flags & IFA_F_MANAGETEMPADDR)
			manage_tempaddrs(idev, ifp, cfg->valid_lft,
					 cfg->preferred_lft, true, jiffies);
		in6_ifa_put(ifp);
		addrconf_verify_rtnl();
		return 0;
	} else if (cfg->ifa_flags & IFA_F_MCAUTOJOIN) {
		ipv6_mc_config(net->ipv6.mc_autojoin_sk, false,
			       cfg->pfx, ifindex);
	}

	return PTR_ERR(ifp);
}