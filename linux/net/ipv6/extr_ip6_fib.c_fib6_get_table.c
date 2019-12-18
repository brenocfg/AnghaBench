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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct fib6_table* fib6_main_tbl; } ;
struct net {TYPE_1__ ipv6; } ;
struct fib6_table {int dummy; } ;

/* Variables and functions */

struct fib6_table *fib6_get_table(struct net *net, u32 id)
{
	  return net->ipv6.fib6_main_tbl;
}