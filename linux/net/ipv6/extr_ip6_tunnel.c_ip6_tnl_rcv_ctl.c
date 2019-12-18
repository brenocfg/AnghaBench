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
struct __ip6_tnl_parm {int flags; scalar_t__ link; } ;
struct ip6_tnl {struct net* net; struct __ip6_tnl_parm parms; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_F_TENTATIVE ; 
 int IP6_TNL_F_ALLOW_LOCAL_REMOTE ; 
 int IP6_TNL_F_CAP_PER_PACKET ; 
 int IP6_TNL_F_CAP_RCV ; 
 struct net_device* dev_get_by_index_rcu (struct net*,scalar_t__) ; 
 int ip6_tnl_get_cap (struct ip6_tnl*,struct in6_addr const*,struct in6_addr const*) ; 
 scalar_t__ ipv6_addr_is_multicast (struct in6_addr const*) ; 
 int ipv6_chk_addr_and_flags (struct net*,struct in6_addr const*,struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

int ip6_tnl_rcv_ctl(struct ip6_tnl *t,
				  const struct in6_addr *laddr,
				  const struct in6_addr *raddr)
{
	struct __ip6_tnl_parm *p = &t->parms;
	int ret = 0;
	struct net *net = t->net;

	if ((p->flags & IP6_TNL_F_CAP_RCV) ||
	    ((p->flags & IP6_TNL_F_CAP_PER_PACKET) &&
	     (ip6_tnl_get_cap(t, laddr, raddr) & IP6_TNL_F_CAP_RCV))) {
		struct net_device *ldev = NULL;

		if (p->link)
			ldev = dev_get_by_index_rcu(net, p->link);

		if ((ipv6_addr_is_multicast(laddr) ||
		     likely(ipv6_chk_addr_and_flags(net, laddr, ldev, false,
						    0, IFA_F_TENTATIVE))) &&
		    ((p->flags & IP6_TNL_F_ALLOW_LOCAL_REMOTE) ||
		     likely(!ipv6_chk_addr_and_flags(net, raddr, ldev, true,
						     0, IFA_F_TENTATIVE))))
			ret = 1;
	}
	return ret;
}