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
struct nf_conntrack_expect {int /*<<< orphan*/  rcu; int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_expect_free_rcu ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void nf_ct_expect_put(struct nf_conntrack_expect *exp)
{
	if (refcount_dec_and_test(&exp->use))
		call_rcu(&exp->rcu, nf_ct_expect_free_rcu);
}