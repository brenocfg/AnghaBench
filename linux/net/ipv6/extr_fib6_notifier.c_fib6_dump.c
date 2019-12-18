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
struct notifier_block {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int fib6_rules_dump (struct net*,struct notifier_block*) ; 
 int fib6_tables_dump (struct net*,struct notifier_block*) ; 

__attribute__((used)) static int fib6_dump(struct net *net, struct notifier_block *nb)
{
	int err;

	err = fib6_rules_dump(net, nb);
	if (err)
		return err;

	return fib6_tables_dump(net, nb);
}