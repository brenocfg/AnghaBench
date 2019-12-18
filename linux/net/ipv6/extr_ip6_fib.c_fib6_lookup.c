#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fib6_main_tbl; } ;
struct net {TYPE_1__ ipv6; } ;
struct flowi6 {int dummy; } ;
struct fib6_result {int dummy; } ;

/* Variables and functions */
 int fib6_table_lookup (struct net*,int /*<<< orphan*/ ,int,struct flowi6*,struct fib6_result*,int) ; 

int fib6_lookup(struct net *net, int oif, struct flowi6 *fl6,
		struct fib6_result *res, int flags)
{
	return fib6_table_lookup(net, net->ipv6.fib6_main_tbl, oif, fl6,
				 res, flags);
}