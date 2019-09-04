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
struct rt6_info {int dummy; } ;
struct net {int dummy; } ;
struct flowi6 {int /*<<< orphan*/  flowi6_iif; } ;
struct fib6_table {int dummy; } ;

/* Variables and functions */
 struct rt6_info* ip6_pol_route (struct net*,struct fib6_table*,int /*<<< orphan*/ ,struct flowi6*,struct sk_buff const*,int) ; 

__attribute__((used)) static struct rt6_info *ip6_pol_route_input(struct net *net,
					    struct fib6_table *table,
					    struct flowi6 *fl6,
					    const struct sk_buff *skb,
					    int flags)
{
	return ip6_pol_route(net, table, fl6->flowi6_iif, fl6, skb, flags);
}