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

/* Variables and functions */
#define  AF_INET6 130 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
#define  PGSQL_AF_INET 129 
#define  PGSQL_AF_INET6 128 
 int /*<<< orphan*/  errno ; 
 char* inet_net_ntop_ipv4 (void const*,int,char*,size_t) ; 
 char* inet_net_ntop_ipv6 (void const*,int,char*,size_t) ; 

char *
pg_inet_net_ntop(int af, const void *src, int bits, char *dst, size_t size)
{
	/*
	 * We need to cover both the address family constants used by the PG inet
	 * type (PGSQL_AF_INET and PGSQL_AF_INET6) and those used by the system
	 * libraries (AF_INET and AF_INET6).  We can safely assume PGSQL_AF_INET
	 * == AF_INET, but the INET6 constants are very likely to be different. If
	 * AF_INET6 isn't defined, silently ignore it.
	 */
	switch (af)
	{
		case PGSQL_AF_INET:
			return (inet_net_ntop_ipv4(src, bits, dst, size));
		case PGSQL_AF_INET6:
#if defined(AF_INET6) && AF_INET6 != PGSQL_AF_INET6
		case AF_INET6:
#endif
			return (inet_net_ntop_ipv6(src, bits, dst, size));
		default:
			errno = EAFNOSUPPORT;
			return (NULL);
	}
}