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
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_LOOPBACK ; 
 int ipv6_addr_type (struct in6_addr const*) ; 

__attribute__((used)) static bool addr_is_local(const struct in6_addr *addr)
{
	return ipv6_addr_type(addr) &
		(IPV6_ADDR_LINKLOCAL | IPV6_ADDR_LOOPBACK);
}