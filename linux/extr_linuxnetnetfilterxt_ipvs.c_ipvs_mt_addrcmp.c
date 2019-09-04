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
union nf_inet_addr {int ip; } ;

/* Variables and functions */
 unsigned int NFPROTO_IPV4 ; 

__attribute__((used)) static bool ipvs_mt_addrcmp(const union nf_inet_addr *kaddr,
			    const union nf_inet_addr *uaddr,
			    const union nf_inet_addr *umask,
			    unsigned int l3proto)
{
	if (l3proto == NFPROTO_IPV4)
		return ((kaddr->ip ^ uaddr->ip) & umask->ip) == 0;
#ifdef CONFIG_IP_VS_IPV6
	else if (l3proto == NFPROTO_IPV6)
		return ipv6_masked_addr_cmp(&kaddr->in6, &umask->in6,
		       &uaddr->in6) == 0;
#endif
	else
		return false;
}