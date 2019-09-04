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
struct rt6key {int plen; struct in6_addr const addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipv6_addr_equal (struct in6_addr const*,struct in6_addr const*) ; 

__attribute__((used)) static inline int ip6_rt_check(const struct rt6key *rt_key,
			       const struct in6_addr *fl_addr,
			       const struct in6_addr *addr_cache)
{
	return (rt_key->plen != 128 || !ipv6_addr_equal(fl_addr, &rt_key->addr)) &&
		(!addr_cache || !ipv6_addr_equal(fl_addr, addr_cache));
}