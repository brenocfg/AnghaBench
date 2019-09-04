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
struct net {int dummy; } ;
struct flowi6 {int dummy; } ;
struct fib6_table {int dummy; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct fib6_info *
eafnosupport_fib6_table_lookup(struct net *net, struct fib6_table *table,
			       int oif, struct flowi6 *fl6, int flags)
{
	return NULL;
}