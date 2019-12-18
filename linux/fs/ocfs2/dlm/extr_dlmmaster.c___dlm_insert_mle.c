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
struct hlist_head {int dummy; } ;
struct dlm_master_list_entry {int /*<<< orphan*/  master_hash_node; int /*<<< orphan*/  mnamehash; } ;
struct dlm_ctxt {int /*<<< orphan*/  master_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 struct hlist_head* dlm_master_hash (struct dlm_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 

void __dlm_insert_mle(struct dlm_ctxt *dlm, struct dlm_master_list_entry *mle)
{
	struct hlist_head *bucket;

	assert_spin_locked(&dlm->master_lock);

	bucket = dlm_master_hash(dlm, mle->mnamehash);
	hlist_add_head(&mle->master_hash_node, bucket);
}