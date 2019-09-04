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
struct ip_tunnel {int dummy; } ;
struct in6_addr {scalar_t__* s6_addr16; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ htons (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 

__attribute__((used)) static bool check_6rd(struct ip_tunnel *tunnel, const struct in6_addr *v6dst,
		      __be32 *v4dst)
{
#ifdef CONFIG_IPV6_SIT_6RD
	if (ipv6_prefix_equal(v6dst, &tunnel->ip6rd.prefix,
			      tunnel->ip6rd.prefixlen)) {
		unsigned int pbw0, pbi0;
		int pbi1;
		u32 d;

		pbw0 = tunnel->ip6rd.prefixlen >> 5;
		pbi0 = tunnel->ip6rd.prefixlen & 0x1f;

		d = tunnel->ip6rd.relay_prefixlen < 32 ?
			(ntohl(v6dst->s6_addr32[pbw0]) << pbi0) >>
		    tunnel->ip6rd.relay_prefixlen : 0;

		pbi1 = pbi0 - tunnel->ip6rd.relay_prefixlen;
		if (pbi1 > 0)
			d |= ntohl(v6dst->s6_addr32[pbw0 + 1]) >>
			     (32 - pbi1);

		*v4dst = tunnel->ip6rd.relay_prefix | htonl(d);
		return true;
	}
#else
	if (v6dst->s6_addr16[0] == htons(0x2002)) {
		/* 6to4 v6 addr has 16 bits prefix, 32 v4addr, 16 SLA, ... */
		memcpy(v4dst, &v6dst->s6_addr16[1], 4);
		return true;
	}
#endif
	return false;
}