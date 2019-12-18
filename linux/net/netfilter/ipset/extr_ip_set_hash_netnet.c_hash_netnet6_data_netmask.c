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
struct hash_netnet6_elem {void** cidr; int /*<<< orphan*/ * ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip6_netmask (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static inline void
hash_netnet6_data_netmask(struct hash_netnet6_elem *elem, u8 cidr, bool inner)
{
	if (inner) {
		ip6_netmask(&elem->ip[1], cidr);
		elem->cidr[1] = cidr;
	} else {
		ip6_netmask(&elem->ip[0], cidr);
		elem->cidr[0] = cidr;
	}
}