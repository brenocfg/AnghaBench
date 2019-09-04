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
struct fib6_table {int /*<<< orphan*/  tb6_lock; } ;
struct fib6_node {int fn_flags; int /*<<< orphan*/  parent; int /*<<< orphan*/  leaf; } ;
struct fib6_info {scalar_t__ rt6i_pcpu; int /*<<< orphan*/  fib6_ref; struct fib6_table* fib6_table; } ;

/* Variables and functions */
 int RTN_RTINFO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fib6_drop_pcpu_from (struct fib6_info*,struct fib6_table*) ; 
 struct fib6_info* fib6_find_prefix (struct net*,struct fib6_table*,struct fib6_node*) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct fib6_info*) ; 
 void* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fib6_purge_rt(struct fib6_info *rt, struct fib6_node *fn,
			  struct net *net)
{
	struct fib6_table *table = rt->fib6_table;

	if (atomic_read(&rt->fib6_ref) != 1) {
		/* This route is used as dummy address holder in some split
		 * nodes. It is not leaked, but it still holds other resources,
		 * which must be released in time. So, scan ascendant nodes
		 * and replace dummy references to this route with references
		 * to still alive ones.
		 */
		while (fn) {
			struct fib6_info *leaf = rcu_dereference_protected(fn->leaf,
					    lockdep_is_held(&table->tb6_lock));
			struct fib6_info *new_leaf;
			if (!(fn->fn_flags & RTN_RTINFO) && leaf == rt) {
				new_leaf = fib6_find_prefix(net, table, fn);
				atomic_inc(&new_leaf->fib6_ref);

				rcu_assign_pointer(fn->leaf, new_leaf);
				fib6_info_release(rt);
			}
			fn = rcu_dereference_protected(fn->parent,
				    lockdep_is_held(&table->tb6_lock));
		}

		if (rt->rt6i_pcpu)
			fib6_drop_pcpu_from(rt, table);
	}
}