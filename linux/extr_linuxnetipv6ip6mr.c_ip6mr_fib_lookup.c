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
struct TYPE_2__ {struct mr_table* mrt6; } ;
struct net {TYPE_1__ ipv6; } ;
struct mr_table {int dummy; } ;
struct flowi6 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ip6mr_fib_lookup(struct net *net, struct flowi6 *flp6,
			    struct mr_table **mrt)
{
	*mrt = net->ipv6.mrt6;
	return 0;
}