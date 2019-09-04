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
struct nf_ct_helper_expectfn {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_conntrack_expect_lock ; 
 int /*<<< orphan*/  nf_ct_helper_expectfn_list ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void nf_ct_helper_expectfn_register(struct nf_ct_helper_expectfn *n)
{
	spin_lock_bh(&nf_conntrack_expect_lock);
	list_add_rcu(&n->head, &nf_ct_helper_expectfn_list);
	spin_unlock_bh(&nf_conntrack_expect_lock);
}