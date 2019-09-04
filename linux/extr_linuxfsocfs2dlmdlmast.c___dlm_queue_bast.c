#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {TYPE_1__ lockname; } ;
struct TYPE_4__ {int /*<<< orphan*/  cookie; } ;
struct dlm_lock {int bast_pending; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  bast_list; TYPE_2__ ml; struct dlm_lock_resource* lockres; } ;
struct dlm_ctxt {int /*<<< orphan*/  pending_basts; int /*<<< orphan*/  name; int /*<<< orphan*/  ast_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_get_lock_cookie_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_get_lock_cookie_seq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_lock_get (struct dlm_lock*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __dlm_queue_bast(struct dlm_ctxt *dlm, struct dlm_lock *lock)
{
	struct dlm_lock_resource *res;

	BUG_ON(!dlm);
	BUG_ON(!lock);

	assert_spin_locked(&dlm->ast_lock);

	res = lock->lockres;

	BUG_ON(!list_empty(&lock->bast_list));
	if (lock->bast_pending)
		mlog(0, "%s: res %.*s, lock %u:%llu, BAST getting flushed\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)));

	/* putting lock on list, add a ref */
	dlm_lock_get(lock);
	spin_lock(&lock->spinlock);
	list_add_tail(&lock->bast_list, &dlm->pending_basts);
	lock->bast_pending = 1;
	spin_unlock(&lock->spinlock);
}