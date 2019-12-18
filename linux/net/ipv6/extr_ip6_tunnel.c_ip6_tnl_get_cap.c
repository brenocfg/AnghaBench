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
struct __ip6_tnl_parm {scalar_t__ link; } ;
struct ip6_tnl {struct __ip6_tnl_parm parms; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IP6_TNL_F_CAP_PER_PACKET ; 
 int /*<<< orphan*/  IP6_TNL_F_CAP_RCV ; 
 int /*<<< orphan*/  IP6_TNL_F_CAP_XMIT ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_LOOPBACK ; 
 int IPV6_ADDR_MULTICAST ; 
 int IPV6_ADDR_UNICAST ; 
 int ipv6_addr_type (struct in6_addr const*) ; 

__u32 ip6_tnl_get_cap(struct ip6_tnl *t,
			     const struct in6_addr *laddr,
			     const struct in6_addr *raddr)
{
	struct __ip6_tnl_parm *p = &t->parms;
	int ltype = ipv6_addr_type(laddr);
	int rtype = ipv6_addr_type(raddr);
	__u32 flags = 0;

	if (ltype == IPV6_ADDR_ANY || rtype == IPV6_ADDR_ANY) {
		flags = IP6_TNL_F_CAP_PER_PACKET;
	} else if (ltype & (IPV6_ADDR_UNICAST|IPV6_ADDR_MULTICAST) &&
		   rtype & (IPV6_ADDR_UNICAST|IPV6_ADDR_MULTICAST) &&
		   !((ltype|rtype) & IPV6_ADDR_LOOPBACK) &&
		   (!((ltype|rtype) & IPV6_ADDR_LINKLOCAL) || p->link)) {
		if (ltype&IPV6_ADDR_UNICAST)
			flags |= IP6_TNL_F_CAP_XMIT;
		if (rtype&IPV6_ADDR_UNICAST)
			flags |= IP6_TNL_F_CAP_RCV;
	}
	return flags;
}