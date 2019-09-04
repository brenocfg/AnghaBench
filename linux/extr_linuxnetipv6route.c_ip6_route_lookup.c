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
struct net {int dummy; } ;
struct flowi6 {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 struct dst_entry* fib6_rule_lookup (struct net*,struct flowi6*,struct sk_buff const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_pol_route_lookup ; 

struct dst_entry *ip6_route_lookup(struct net *net, struct flowi6 *fl6,
				   const struct sk_buff *skb, int flags)
{
	return fib6_rule_lookup(net, fl6, skb, flags, ip6_pol_route_lookup);
}