#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct hash_netportnet6_elem {scalar_t__ ccmp; scalar_t__ port; scalar_t__ proto; TYPE_1__* ip; } ;
struct TYPE_2__ {int /*<<< orphan*/  in6; } ;

/* Variables and functions */
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
hash_netportnet6_data_equal(const struct hash_netportnet6_elem *ip1,
			    const struct hash_netportnet6_elem *ip2,
			    u32 *multi)
{
	return ipv6_addr_equal(&ip1->ip[0].in6, &ip2->ip[0].in6) &&
	       ipv6_addr_equal(&ip1->ip[1].in6, &ip2->ip[1].in6) &&
	       ip1->ccmp == ip2->ccmp &&
	       ip1->port == ip2->port &&
	       ip1->proto == ip2->proto;
}