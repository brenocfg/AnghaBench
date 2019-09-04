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
typedef  scalar_t__ u8 ;
struct hash_ipportnet6_elem {scalar_t__ cidr; int /*<<< orphan*/  ip2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip6_netmask (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline void
hash_ipportnet6_data_netmask(struct hash_ipportnet6_elem *elem, u8 cidr)
{
	ip6_netmask(&elem->ip2, cidr);
	elem->cidr = cidr - 1;
}