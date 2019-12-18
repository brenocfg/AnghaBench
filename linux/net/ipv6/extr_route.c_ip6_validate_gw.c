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
struct netlink_ext_ack {int dummy; } ;
struct net_device {int flags; } ;
struct net {int dummy; } ;
struct inet6_dev {int dummy; } ;
struct in6_addr {int dummy; } ;
struct fib6_config {int fc_flags; struct in6_addr fc_gateway; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFF_LOOPBACK ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_MAPPED ; 
 int IPV6_ADDR_UNICAST ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int RTNH_F_ONLINK ; 
 int ip6_route_check_nh (struct net*,struct fib6_config*,struct net_device**,struct inet6_dev**) ; 
 int ip6_route_check_nh_onlink (struct net*,struct fib6_config*,struct net_device const*,struct netlink_ext_ack*) ; 
 int ipv6_addr_type (struct in6_addr const*) ; 
 scalar_t__ ipv6_chk_addr_and_flags (struct net*,struct in6_addr const*,struct net_device const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int ip6_validate_gw(struct net *net, struct fib6_config *cfg,
			   struct net_device **_dev, struct inet6_dev **idev,
			   struct netlink_ext_ack *extack)
{
	const struct in6_addr *gw_addr = &cfg->fc_gateway;
	int gwa_type = ipv6_addr_type(gw_addr);
	bool skip_dev = gwa_type & IPV6_ADDR_LINKLOCAL ? false : true;
	const struct net_device *dev = *_dev;
	bool need_addr_check = !dev;
	int err = -EINVAL;

	/* if gw_addr is local we will fail to detect this in case
	 * address is still TENTATIVE (DAD in progress). rt6_lookup()
	 * will return already-added prefix route via interface that
	 * prefix route was assigned to, which might be non-loopback.
	 */
	if (dev &&
	    ipv6_chk_addr_and_flags(net, gw_addr, dev, skip_dev, 0, 0)) {
		NL_SET_ERR_MSG(extack, "Gateway can not be a local address");
		goto out;
	}

	if (gwa_type != (IPV6_ADDR_LINKLOCAL | IPV6_ADDR_UNICAST)) {
		/* IPv6 strictly inhibits using not link-local
		 * addresses as nexthop address.
		 * Otherwise, router will not able to send redirects.
		 * It is very good, but in some (rare!) circumstances
		 * (SIT, PtP, NBMA NOARP links) it is handy to allow
		 * some exceptions. --ANK
		 * We allow IPv4-mapped nexthops to support RFC4798-type
		 * addressing
		 */
		if (!(gwa_type & (IPV6_ADDR_UNICAST | IPV6_ADDR_MAPPED))) {
			NL_SET_ERR_MSG(extack, "Invalid gateway address");
			goto out;
		}

		rcu_read_lock();

		if (cfg->fc_flags & RTNH_F_ONLINK)
			err = ip6_route_check_nh_onlink(net, cfg, dev, extack);
		else
			err = ip6_route_check_nh(net, cfg, _dev, idev);

		rcu_read_unlock();

		if (err)
			goto out;
	}

	/* reload in case device was changed */
	dev = *_dev;

	err = -EINVAL;
	if (!dev) {
		NL_SET_ERR_MSG(extack, "Egress device not specified");
		goto out;
	} else if (dev->flags & IFF_LOOPBACK) {
		NL_SET_ERR_MSG(extack,
			       "Egress device can not be loopback device for this route");
		goto out;
	}

	/* if we did not check gw_addr above, do so now that the
	 * egress device has been resolved.
	 */
	if (need_addr_check &&
	    ipv6_chk_addr_and_flags(net, gw_addr, dev, skip_dev, 0, 0)) {
		NL_SET_ERR_MSG(extack, "Gateway can not be a local address");
		goto out;
	}

	err = 0;
out:
	return err;
}