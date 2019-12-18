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
typedef  int __be32 ;

/* Variables and functions */
 int SEL_NETNODE_HASH_SIZE ; 

__attribute__((used)) static unsigned int sel_netnode_hashfn_ipv4(__be32 addr)
{
	/* at some point we should determine if the mismatch in byte order
	 * affects the hash function dramatically */
	return (addr & (SEL_NETNODE_HASH_SIZE - 1));
}