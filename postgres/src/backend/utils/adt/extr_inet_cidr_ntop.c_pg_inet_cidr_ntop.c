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
 char* inet_cidr_ntop_ipv4 (void const*,int,char*,size_t) ; 
 char* inet_cidr_ntop_ipv6 (void const*,int,char*,size_t) ; 

char *
pg_inet_cidr_ntop(int af, const void *src, int bits, char *dst, size_t size)
{
	switch (af)
	{
		case PGSQL_AF_INET:
			return inet_cidr_ntop_ipv4(src, bits, dst, size);
		case PGSQL_AF_INET6:
			return inet_cidr_ntop_ipv6(src, bits, dst, size);
		default:
			errno = EAFNOSUPPORT;
			return NULL;
	}
}