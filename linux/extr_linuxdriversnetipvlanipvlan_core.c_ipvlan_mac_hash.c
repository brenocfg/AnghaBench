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
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int IPVLAN_MAC_FILTER_MASK ; 
 int /*<<< orphan*/  __get_unaligned_cpu32 (unsigned char const*) ; 
 int /*<<< orphan*/  ipvlan_jhash_secret ; 
 unsigned int jhash_1word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int ipvlan_mac_hash(const unsigned char *addr)
{
	u32 hash = jhash_1word(__get_unaligned_cpu32(addr+2),
			       ipvlan_jhash_secret);

	return hash & IPVLAN_MAC_FILTER_MASK;
}