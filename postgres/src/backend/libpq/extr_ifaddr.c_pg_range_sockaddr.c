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
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int range_sockaddr_AF_INET (struct sockaddr_in const*,struct sockaddr_in const*,struct sockaddr_in const*) ; 
 int range_sockaddr_AF_INET6 (struct sockaddr_in6 const*,struct sockaddr_in6 const*,struct sockaddr_in6 const*) ; 

int
pg_range_sockaddr(const struct sockaddr_storage *addr,
				  const struct sockaddr_storage *netaddr,
				  const struct sockaddr_storage *netmask)
{
	if (addr->ss_family == AF_INET)
		return range_sockaddr_AF_INET((const struct sockaddr_in *) addr,
									  (const struct sockaddr_in *) netaddr,
									  (const struct sockaddr_in *) netmask);
#ifdef HAVE_IPV6
	else if (addr->ss_family == AF_INET6)
		return range_sockaddr_AF_INET6((const struct sockaddr_in6 *) addr,
									   (const struct sockaddr_in6 *) netaddr,
									   (const struct sockaddr_in6 *) netmask);
#endif
	else
		return 0;
}