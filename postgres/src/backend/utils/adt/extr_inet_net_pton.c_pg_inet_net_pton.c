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
 int /*<<< orphan*/  EAFNOSUPPORT ; 
#define  PGSQL_AF_INET 129 
#define  PGSQL_AF_INET6 128 
 int /*<<< orphan*/  errno ; 
 int inet_cidr_pton_ipv4 (char const*,void*,size_t) ; 
 int inet_cidr_pton_ipv6 (char const*,void*,size_t) ; 
 int inet_net_pton_ipv4 (char const*,void*) ; 
 int inet_net_pton_ipv6 (char const*,void*) ; 

int
pg_inet_net_pton(int af, const char *src, void *dst, size_t size)
{
	switch (af)
	{
		case PGSQL_AF_INET:
			return size == -1 ?
				inet_net_pton_ipv4(src, dst) :
				inet_cidr_pton_ipv4(src, dst, size);
		case PGSQL_AF_INET6:
			return size == -1 ?
				inet_net_pton_ipv6(src, dst) :
				inet_cidr_pton_ipv6(src, dst, size);
		default:
			errno = EAFNOSUPPORT;
			return -1;
	}
}