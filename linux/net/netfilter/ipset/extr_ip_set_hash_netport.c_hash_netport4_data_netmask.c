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
struct hash_netport4_elem {scalar_t__ cidr; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_set_netmask (scalar_t__) ; 

__attribute__((used)) static inline void
hash_netport4_data_netmask(struct hash_netport4_elem *elem, u8 cidr)
{
	elem->ip &= ip_set_netmask(cidr);
	elem->cidr = cidr - 1;
}