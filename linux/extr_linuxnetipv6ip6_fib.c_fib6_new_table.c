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
typedef  int /*<<< orphan*/  u32 ;
struct net {int dummy; } ;
struct fib6_table {int dummy; } ;

/* Variables and functions */
 struct fib6_table* fib6_get_table (struct net*,int /*<<< orphan*/ ) ; 

struct fib6_table *fib6_new_table(struct net *net, u32 id)
{
	return fib6_get_table(net, id);
}