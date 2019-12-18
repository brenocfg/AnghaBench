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
struct ip6addrlbl_entry {int ifindex; int addrtype; int /*<<< orphan*/  prefixlen; int /*<<< orphan*/  prefix; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipv6_prefix_equal (struct in6_addr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __ip6addrlbl_match(const struct ip6addrlbl_entry *p,
			       const struct in6_addr *addr,
			       int addrtype, int ifindex)
{
	if (p->ifindex && p->ifindex != ifindex)
		return false;
	if (p->addrtype && p->addrtype != addrtype)
		return false;
	if (!ipv6_prefix_equal(addr, &p->prefix, p->prefixlen))
		return false;
	return true;
}