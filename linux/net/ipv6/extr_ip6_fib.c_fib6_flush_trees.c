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

/* Variables and functions */
 int /*<<< orphan*/  __fib6_clean_all (struct net*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int fib6_new_sernum (struct net*) ; 

__attribute__((used)) static void fib6_flush_trees(struct net *net)
{
	int new_sernum = fib6_new_sernum(net);

	__fib6_clean_all(net, NULL, new_sernum, NULL, false);
}