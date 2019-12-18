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
typedef  void* u8 ;
struct hash_netnet4_elem {void** cidr; int /*<<< orphan*/ * ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_set_netmask (void*) ; 

__attribute__((used)) static inline void
hash_netnet4_data_netmask(struct hash_netnet4_elem *elem, u8 cidr, bool inner)
{
	if (inner) {
		elem->ip[1] &= ip_set_netmask(cidr);
		elem->cidr[1] = cidr;
	} else {
		elem->ip[0] &= ip_set_netmask(cidr);
		elem->cidr[0] = cidr;
	}
}