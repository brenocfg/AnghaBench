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
struct TYPE_2__ {struct mr_table* mrt; } ;
struct net {TYPE_1__ ipv4; } ;
struct mr_table {int dummy; } ;
struct flowi4 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ipmr_fib_lookup(struct net *net, struct flowi4 *flp4,
			   struct mr_table **mrt)
{
	*mrt = net->ipv4.mrt;
	return 0;
}