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
struct fib6_node {int fn_sernum; int /*<<< orphan*/  parent; } ;
struct fib6_info {TYPE_1__* fib6_table; int /*<<< orphan*/  fib6_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  tb6_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct fib6_node* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void __fib6_update_sernum_upto_root(struct fib6_info *rt,
					   int sernum)
{
	struct fib6_node *fn = rcu_dereference_protected(rt->fib6_node,
				lockdep_is_held(&rt->fib6_table->tb6_lock));

	/* paired with smp_rmb() in rt6_get_cookie_safe() */
	smp_wmb();
	while (fn) {
		fn->fn_sernum = sernum;
		fn = rcu_dereference_protected(fn->parent,
				lockdep_is_held(&rt->fib6_table->tb6_lock));
	}
}