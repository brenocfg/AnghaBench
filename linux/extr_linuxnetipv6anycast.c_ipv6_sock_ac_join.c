#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_7__ {struct net_device* dev; } ;
struct rt6_info {TYPE_3__ dst; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_6__ {TYPE_1__* devconf_all; } ;
struct net {int /*<<< orphan*/  user_ns; TYPE_2__ ipv6; } ;
struct ipv6_pinfo {struct ipv6_ac_socklist* ipv6_ac_list; } ;
struct in6_addr {int dummy; } ;
struct ipv6_ac_socklist {struct ipv6_ac_socklist* acl_next; int /*<<< orphan*/  acl_ifindex; struct in6_addr acl_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  forwarding; } ;
struct inet6_dev {TYPE_4__ cnf; } ;
struct TYPE_5__ {int /*<<< orphan*/  forwarding; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFA_F_TENTATIVE ; 
 int IFF_LOOPBACK ; 
 int IFF_UP ; 
 struct net_device* __dev_get_by_flags (struct net*,int,int) ; 
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int __ipv6_dev_ac_inc (struct inet6_dev*,struct in6_addr const*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_rt_put (struct rt6_info*) ; 
 scalar_t__ ipv6_addr_is_multicast (struct in6_addr const*) ; 
 scalar_t__ ipv6_chk_addr_and_flags (struct net*,struct in6_addr const*,struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_chk_prefix (struct in6_addr const*,struct net_device*) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rt6_info* rt6_lookup (struct net*,struct in6_addr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct ipv6_ac_socklist*,int) ; 
 struct ipv6_ac_socklist* sock_kmalloc (struct sock*,int,int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 

int ipv6_sock_ac_join(struct sock *sk, int ifindex, const struct in6_addr *addr)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct net_device *dev = NULL;
	struct inet6_dev *idev;
	struct ipv6_ac_socklist *pac;
	struct net *net = sock_net(sk);
	int	ishost = !net->ipv6.devconf_all->forwarding;
	int	err = 0;

	ASSERT_RTNL();

	if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		return -EPERM;
	if (ipv6_addr_is_multicast(addr))
		return -EINVAL;

	if (ifindex)
		dev = __dev_get_by_index(net, ifindex);

	if (ipv6_chk_addr_and_flags(net, addr, dev, true, 0, IFA_F_TENTATIVE))
		return -EINVAL;

	pac = sock_kmalloc(sk, sizeof(struct ipv6_ac_socklist), GFP_KERNEL);
	if (!pac)
		return -ENOMEM;
	pac->acl_next = NULL;
	pac->acl_addr = *addr;

	if (ifindex == 0) {
		struct rt6_info *rt;

		rt = rt6_lookup(net, addr, NULL, 0, NULL, 0);
		if (rt) {
			dev = rt->dst.dev;
			ip6_rt_put(rt);
		} else if (ishost) {
			err = -EADDRNOTAVAIL;
			goto error;
		} else {
			/* router, no matching interface: just pick one */
			dev = __dev_get_by_flags(net, IFF_UP,
						 IFF_UP | IFF_LOOPBACK);
		}
	}

	if (!dev) {
		err = -ENODEV;
		goto error;
	}

	idev = __in6_dev_get(dev);
	if (!idev) {
		if (ifindex)
			err = -ENODEV;
		else
			err = -EADDRNOTAVAIL;
		goto error;
	}
	/* reset ishost, now that we have a specific device */
	ishost = !idev->cnf.forwarding;

	pac->acl_ifindex = dev->ifindex;

	/* XXX
	 * For hosts, allow link-local or matching prefix anycasts.
	 * This obviates the need for propagating anycast routes while
	 * still allowing some non-router anycast participation.
	 */
	if (!ipv6_chk_prefix(addr, dev)) {
		if (ishost)
			err = -EADDRNOTAVAIL;
		if (err)
			goto error;
	}

	err = __ipv6_dev_ac_inc(idev, addr);
	if (!err) {
		pac->acl_next = np->ipv6_ac_list;
		np->ipv6_ac_list = pac;
		pac = NULL;
	}

error:
	if (pac)
		sock_kfree_s(sk, pac, sizeof(*pac));
	return err;
}