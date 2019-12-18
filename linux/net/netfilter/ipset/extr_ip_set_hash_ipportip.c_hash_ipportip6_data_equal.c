#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  in6; } ;
struct TYPE_3__ {int /*<<< orphan*/  in6; } ;
struct hash_ipportip6_elem {scalar_t__ port; scalar_t__ proto; TYPE_2__ ip2; TYPE_1__ ip; } ;

/* Variables and functions */
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
hash_ipportip6_data_equal(const struct hash_ipportip6_elem *ip1,
			  const struct hash_ipportip6_elem *ip2,
			  u32 *multi)
{
	return ipv6_addr_equal(&ip1->ip.in6, &ip2->ip.in6) &&
	       ipv6_addr_equal(&ip1->ip2.in6, &ip2->ip2.in6) &&
	       ip1->port == ip2->port &&
	       ip1->proto == ip2->proto;
}