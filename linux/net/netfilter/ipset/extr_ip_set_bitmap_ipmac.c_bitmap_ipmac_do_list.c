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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct bitmap_ipmac_elem {scalar_t__ filled; int /*<<< orphan*/  ether; } ;
struct bitmap_ipmac {scalar_t__ first_ip; int /*<<< orphan*/  extensions; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IPSET_ATTR_ETHER ; 
 int /*<<< orphan*/  IPSET_ATTR_IP ; 
 scalar_t__ MAC_FILLED ; 
 struct bitmap_ipmac_elem* get_const_elem (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_ipaddr4 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bitmap_ipmac_do_list(struct sk_buff *skb, const struct bitmap_ipmac *map,
		     u32 id, size_t dsize)
{
	const struct bitmap_ipmac_elem *elem =
		get_const_elem(map->extensions, id, dsize);

	return nla_put_ipaddr4(skb, IPSET_ATTR_IP,
			       htonl(map->first_ip + id)) ||
	       (elem->filled == MAC_FILLED &&
		nla_put(skb, IPSET_ATTR_ETHER, ETH_ALEN, elem->ether));
}