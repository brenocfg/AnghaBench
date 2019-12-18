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
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN6_ADDR_HSIZE_SHIFT ; 
 int hash_32 (int,int /*<<< orphan*/ ) ; 
 int ipv6_addr_hash (struct in6_addr const*) ; 
 int net_hash_mix (struct net*) ; 

__attribute__((used)) static u32 inet6_acaddr_hash(struct net *net, const struct in6_addr *addr)
{
	u32 val = ipv6_addr_hash(addr) ^ net_hash_mix(net);

	return hash_32(val, IN6_ADDR_HSIZE_SHIFT);
}