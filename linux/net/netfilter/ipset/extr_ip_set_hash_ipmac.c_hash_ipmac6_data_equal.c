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
struct TYPE_2__ {int /*<<< orphan*/  in6; } ;
struct hash_ipmac6_elem {int /*<<< orphan*/  ether; TYPE_1__ ip; } ;

/* Variables and functions */
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
hash_ipmac6_data_equal(const struct hash_ipmac6_elem *e1,
		       const struct hash_ipmac6_elem *e2,
		       u32 *multi)
{
	return ipv6_addr_equal(&e1->ip.in6, &e2->ip.in6) &&
		ether_addr_equal(e1->ether, e2->ether);
}