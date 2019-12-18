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
union nf_inet_addr {int ip; int* ip6; } ;
typedef  int __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int AF_INET6 ; 
 int /*<<< orphan*/  IP_VS_SH_TAB_BITS ; 
 unsigned int IP_VS_SH_TAB_MASK ; 
 unsigned int hash_32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int
ip_vs_sh_hashkey(int af, const union nf_inet_addr *addr,
		 __be16 port, unsigned int offset)
{
	__be32 addr_fold = addr->ip;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		addr_fold = addr->ip6[0]^addr->ip6[1]^
			    addr->ip6[2]^addr->ip6[3];
#endif
	return (offset + hash_32(ntohs(port) + ntohl(addr_fold),
				 IP_VS_SH_TAB_BITS)) &
		IP_VS_SH_TAB_MASK;
}