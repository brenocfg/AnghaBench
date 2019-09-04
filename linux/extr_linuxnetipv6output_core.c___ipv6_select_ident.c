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
 int __ipv6_addr_jhash (struct in6_addr const*,int) ; 
 int ip_idents_reserve (int,int) ; 
 int net_hash_mix (struct net*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 __ipv6_select_ident(struct net *net, u32 hashrnd,
			       const struct in6_addr *dst,
			       const struct in6_addr *src)
{
	u32 hash, id;

	hash = __ipv6_addr_jhash(dst, hashrnd);
	hash = __ipv6_addr_jhash(src, hash);
	hash ^= net_hash_mix(net);

	/* Treat id of 0 as unset and if we get 0 back from ip_idents_reserve,
	 * set the hight order instead thus minimizing possible future
	 * collisions.
	 */
	id = ip_idents_reserve(hash, 1);
	if (unlikely(!id))
		id = 1 << 31;

	return id;
}