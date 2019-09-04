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
struct TYPE_2__ {struct fib6_info* fib6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct flowi6 {int flowi6_flags; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct fib6_table {int /*<<< orphan*/  tb6_root; } ;
struct fib6_node {int dummy; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 int FLOWI_FLAG_SKIP_NH_OIF ; 
 int RT6_LOOKUP_F_REACHABLE ; 
 struct fib6_node* fib6_backtrack (struct fib6_node*,int /*<<< orphan*/ *) ; 
 struct fib6_node* fib6_node_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct fib6_info* rt6_select (struct net*,struct fib6_node*,int,int) ; 
 int /*<<< orphan*/  trace_fib6_table_lookup (struct net*,struct fib6_info*,struct fib6_table*,struct flowi6*) ; 

struct fib6_info *fib6_table_lookup(struct net *net, struct fib6_table *table,
				    int oif, struct flowi6 *fl6, int strict)
{
	struct fib6_node *fn, *saved_fn;
	struct fib6_info *f6i;

	fn = fib6_node_lookup(&table->tb6_root, &fl6->daddr, &fl6->saddr);
	saved_fn = fn;

	if (fl6->flowi6_flags & FLOWI_FLAG_SKIP_NH_OIF)
		oif = 0;

redo_rt6_select:
	f6i = rt6_select(net, fn, oif, strict);
	if (f6i == net->ipv6.fib6_null_entry) {
		fn = fib6_backtrack(fn, &fl6->saddr);
		if (fn)
			goto redo_rt6_select;
		else if (strict & RT6_LOOKUP_F_REACHABLE) {
			/* also consider unreachable route */
			strict &= ~RT6_LOOKUP_F_REACHABLE;
			fn = saved_fn;
			goto redo_rt6_select;
		}
	}

	trace_fib6_table_lookup(net, f6i, table, fl6);

	return f6i;
}