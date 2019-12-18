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
struct hlist_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; int /*<<< orphan*/  hash; } ;
struct dlm_lock_resource {TYPE_1__ lockname; int /*<<< orphan*/  hash_node; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_lockres_get (struct dlm_lock_resource*) ; 
 struct hlist_head* dlm_lockres_hash (struct dlm_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __dlm_insert_lockres(struct dlm_ctxt *dlm, struct dlm_lock_resource *res)
{
	struct hlist_head *bucket;

	assert_spin_locked(&dlm->spinlock);

	bucket = dlm_lockres_hash(dlm, res->lockname.hash);

	/* get a reference for our hashtable */
	dlm_lockres_get(res);

	hlist_add_head(&res->hash_node, bucket);

	mlog(0, "%s: Hash res %.*s\n", dlm->name, res->lockname.len,
	     res->lockname.name);
}