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
typedef  int u32 ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6_VTI_HASH_SIZE_SHIFT ; 
 int hash_32 (int,int /*<<< orphan*/ ) ; 
 int ipv6_addr_hash (struct in6_addr const*) ; 

__attribute__((used)) static u32 HASH(const struct in6_addr *addr1, const struct in6_addr *addr2)
{
	u32 hash = ipv6_addr_hash(addr1) ^ ipv6_addr_hash(addr2);

	return hash_32(hash, IP6_VTI_HASH_SIZE_SHIFT);
}