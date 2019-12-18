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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct __ip6_tnl_parm {int flags; int /*<<< orphan*/  name; scalar_t__ link; scalar_t__ collect_md; } ;
struct ip6_tnl {struct __ip6_tnl_parm parms; struct net* net; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_F_TENTATIVE ; 
 int IP6_TNL_F_ALLOW_LOCAL_REMOTE ; 
 int IP6_TNL_F_CAP_PER_PACKET ; 
 int IP6_TNL_F_CAP_XMIT ; 
 struct net_device* dev_get_by_index_rcu (struct net*,scalar_t__) ; 
 int ip6_tnl_get_cap (struct ip6_tnl*,struct in6_addr const*,struct in6_addr const*) ; 
 int /*<<< orphan*/  ipv6_addr_is_multicast (struct in6_addr const*) ; 
 int ipv6_chk_addr_and_flags (struct net*,struct in6_addr const*,struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

int ip6_tnl_xmit_ctl(struct ip6_tnl *t,
		     const struct in6_addr *laddr,
		     const struct in6_addr *raddr)
{
	struct __ip6_tnl_parm *p = &t->parms;
	int ret = 0;
	struct net *net = t->net;

	if (t->parms.collect_md)
		return 1;

	if ((p->flags & IP6_TNL_F_CAP_XMIT) ||
	    ((p->flags & IP6_TNL_F_CAP_PER_PACKET) &&
	     (ip6_tnl_get_cap(t, laddr, raddr) & IP6_TNL_F_CAP_XMIT))) {
		struct net_device *ldev = NULL;

		rcu_read_lock();
		if (p->link)
			ldev = dev_get_by_index_rcu(net, p->link);

		if (unlikely(!ipv6_chk_addr_and_flags(net, laddr, ldev, false,
						      0, IFA_F_TENTATIVE)))
			pr_warn("%s xmit: Local address not yet configured!\n",
				p->name);
		else if (!(p->flags & IP6_TNL_F_ALLOW_LOCAL_REMOTE) &&
			 !ipv6_addr_is_multicast(raddr) &&
			 unlikely(ipv6_chk_addr_and_flags(net, raddr, ldev,
							  true, 0, IFA_F_TENTATIVE)))
			pr_warn("%s xmit: Routing loop! Remote address found on this node!\n",
				p->name);
		else
			ret = 1;
		rcu_read_unlock();
	}
	return ret;
}