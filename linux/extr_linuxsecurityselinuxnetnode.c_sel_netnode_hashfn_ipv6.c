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
struct in6_addr {int* s6_addr32; } ;

/* Variables and functions */
 int SEL_NETNODE_HASH_SIZE ; 

__attribute__((used)) static unsigned int sel_netnode_hashfn_ipv6(const struct in6_addr *addr)
{
	/* just hash the least significant 32 bits to keep things fast (they
	 * are the most likely to be different anyway), we can revisit this
	 * later if needed */
	return (addr->s6_addr32[3] & (SEL_NETNODE_HASH_SIZE - 1));
}