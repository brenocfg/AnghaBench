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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  in6; } ;
struct hash_netiface6_elem {scalar_t__ cidr; scalar_t__ physdev; int /*<<< orphan*/  iface; TYPE_1__ ip; } ;

/* Variables and functions */
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
hash_netiface6_data_equal(const struct hash_netiface6_elem *ip1,
			  const struct hash_netiface6_elem *ip2,
			  u32 *multi)
{
	return ipv6_addr_equal(&ip1->ip.in6, &ip2->ip.in6) &&
	       ip1->cidr == ip2->cidr &&
	       (++*multi) &&
	       ip1->physdev == ip2->physdev &&
	       strcmp(ip1->iface, ip2->iface) == 0;
}