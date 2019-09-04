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
struct sk_buff {int dummy; } ;
struct bitmap_ip {int hosts; scalar_t__ first_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSET_ATTR_IP ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int nla_put_ipaddr4 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bitmap_ip_do_list(struct sk_buff *skb, const struct bitmap_ip *map, u32 id,
		  size_t dsize)
{
	return nla_put_ipaddr4(skb, IPSET_ATTR_IP,
			htonl(map->first_ip + id * map->hosts));
}