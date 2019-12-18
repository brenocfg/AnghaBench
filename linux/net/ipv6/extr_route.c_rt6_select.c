#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct fib6_info* fib6_null_entry; } ;
struct net {TYPE_4__ ipv6; } ;
struct fib6_result {struct fib6_info* f6i; int /*<<< orphan*/  fib6_type; int /*<<< orphan*/  fib6_flags; int /*<<< orphan*/  nh; } ;
struct fib6_node {int fn_bit; int /*<<< orphan*/  rr_ptr; int /*<<< orphan*/  leaf; } ;
struct TYPE_6__ {int plen; } ;
struct TYPE_5__ {int plen; } ;
struct fib6_info {scalar_t__ fib6_metric; int /*<<< orphan*/  fib6_type; int /*<<< orphan*/  fib6_flags; int /*<<< orphan*/  fib6_nh; TYPE_3__* fib6_table; scalar_t__ fib6_node; int /*<<< orphan*/  fib6_next; TYPE_2__ fib6_src; TYPE_1__ fib6_dst; } ;
struct TYPE_7__ {int /*<<< orphan*/  tb6_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_rr_leaf (struct fib6_node*,struct fib6_info*,struct fib6_info*,int,int,int*,struct fib6_result*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct fib6_info*) ; 
 struct fib6_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt6_select(struct net *net, struct fib6_node *fn, int oif,
		       struct fib6_result *res, int strict)
{
	struct fib6_info *leaf = rcu_dereference(fn->leaf);
	struct fib6_info *rt0;
	bool do_rr = false;
	int key_plen;

	/* make sure this function or its helpers sets f6i */
	res->f6i = NULL;

	if (!leaf || leaf == net->ipv6.fib6_null_entry)
		goto out;

	rt0 = rcu_dereference(fn->rr_ptr);
	if (!rt0)
		rt0 = leaf;

	/* Double check to make sure fn is not an intermediate node
	 * and fn->leaf does not points to its child's leaf
	 * (This might happen if all routes under fn are deleted from
	 * the tree and fib6_repair_tree() is called on the node.)
	 */
	key_plen = rt0->fib6_dst.plen;
#ifdef CONFIG_IPV6_SUBTREES
	if (rt0->fib6_src.plen)
		key_plen = rt0->fib6_src.plen;
#endif
	if (fn->fn_bit != key_plen)
		goto out;

	find_rr_leaf(fn, leaf, rt0, oif, strict, &do_rr, res);
	if (do_rr) {
		struct fib6_info *next = rcu_dereference(rt0->fib6_next);

		/* no entries matched; do round-robin */
		if (!next || next->fib6_metric != rt0->fib6_metric)
			next = leaf;

		if (next != rt0) {
			spin_lock_bh(&leaf->fib6_table->tb6_lock);
			/* make sure next is not being deleted from the tree */
			if (next->fib6_node)
				rcu_assign_pointer(fn->rr_ptr, next);
			spin_unlock_bh(&leaf->fib6_table->tb6_lock);
		}
	}

out:
	if (!res->f6i) {
		res->f6i = net->ipv6.fib6_null_entry;
		res->nh = res->f6i->fib6_nh;
		res->fib6_flags = res->f6i->fib6_flags;
		res->fib6_type = res->f6i->fib6_type;
	}
}