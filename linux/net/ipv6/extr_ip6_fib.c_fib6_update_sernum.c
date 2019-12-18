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
struct net {int dummy; } ;
struct fib6_node {int /*<<< orphan*/  fn_sernum; } ;
struct fib6_info {TYPE_1__* fib6_table; int /*<<< orphan*/  fib6_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  tb6_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_new_sernum (struct net*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct fib6_node* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fib6_update_sernum(struct net *net, struct fib6_info *f6i)
{
	struct fib6_node *fn;

	fn = rcu_dereference_protected(f6i->fib6_node,
			lockdep_is_held(&f6i->fib6_table->tb6_lock));
	if (fn)
		fn->fn_sernum = fib6_new_sernum(net);
}