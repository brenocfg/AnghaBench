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
struct sk_buff {int dummy; } ;
struct bitmap_ipmac {int /*<<< orphan*/  last_ip; int /*<<< orphan*/  first_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSET_ATTR_IP ; 
 int /*<<< orphan*/  IPSET_ATTR_IP_TO ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_ipaddr4 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bitmap_ipmac_do_head(struct sk_buff *skb, const struct bitmap_ipmac *map)
{
	return nla_put_ipaddr4(skb, IPSET_ATTR_IP, htonl(map->first_ip)) ||
	       nla_put_ipaddr4(skb, IPSET_ATTR_IP_TO, htonl(map->last_ip));
}