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
struct in6_addr {scalar_t__* s6_addr32; } ;

/* Variables and functions */
 scalar_t__ ipv6_addr_v4mapped (struct in6_addr const*) ; 

__attribute__((used)) static bool ipv6_mapped_addr_any(const struct in6_addr *a)
{
	return ipv6_addr_v4mapped(a) && (a->s6_addr32[3] == 0);
}