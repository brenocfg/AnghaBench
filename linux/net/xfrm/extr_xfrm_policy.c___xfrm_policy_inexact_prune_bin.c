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
struct xfrm_pol_inexact_bin {int /*<<< orphan*/  inexact_bins; int /*<<< orphan*/  head; int /*<<< orphan*/  hhead; int /*<<< orphan*/  root_s; int /*<<< orphan*/  root_d; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct xfrm_pol_inexact_bin*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 scalar_t__ rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_pol_inexact_params ; 
 int /*<<< orphan*/  xfrm_policy_inexact_gc_tree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfrm_policy_inexact_table ; 

__attribute__((used)) static void __xfrm_policy_inexact_prune_bin(struct xfrm_pol_inexact_bin *b, bool net_exit)
{
	write_seqcount_begin(&b->count);
	xfrm_policy_inexact_gc_tree(&b->root_d, net_exit);
	xfrm_policy_inexact_gc_tree(&b->root_s, net_exit);
	write_seqcount_end(&b->count);

	if (!RB_EMPTY_ROOT(&b->root_d) || !RB_EMPTY_ROOT(&b->root_s) ||
	    !hlist_empty(&b->hhead)) {
		WARN_ON_ONCE(net_exit);
		return;
	}

	if (rhashtable_remove_fast(&xfrm_policy_inexact_table, &b->head,
				   xfrm_pol_inexact_params) == 0) {
		list_del(&b->inexact_bins);
		kfree_rcu(b, rcu);
	}
}