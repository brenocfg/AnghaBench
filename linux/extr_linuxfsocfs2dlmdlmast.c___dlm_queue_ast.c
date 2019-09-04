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
struct TYPE_4__ {int /*<<< orphan*/  highest_blocked; int /*<<< orphan*/  cookie; int /*<<< orphan*/  type; } ;
struct dlm_lock {int ast_pending; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  ast_list; TYPE_2__ ml; int /*<<< orphan*/  bast_list; scalar_t__ bast_pending; struct dlm_lock_resource* lockres; } ;
struct dlm_ctxt {int /*<<< orphan*/  pending_asts; int /*<<< orphan*/  name; int /*<<< orphan*/  ast_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  LKM_IVMODE ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_get_lock_cookie_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_get_lock_cookie_seq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_lock_get (struct dlm_lock*) ; 
 int /*<<< orphan*/  dlm_lock_put (struct dlm_lock*) ; 
 int /*<<< orphan*/  dlm_lockres_release_ast (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 scalar_t__ dlm_should_cancel_bast (struct dlm_ctxt*,struct dlm_lock*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __dlm_queue_ast(struct dlm_ctxt *dlm, struct dlm_lock *lock)
{
	struct dlm_lock_resource *res;

	BUG_ON(!dlm);
	BUG_ON(!lock);

	res = lock->lockres;

	assert_spin_locked(&dlm->ast_lock);

	if (!list_empty(&lock->ast_list)) {
		mlog(ML_ERROR, "%s: res %.*s, lock %u:%llu, "
		     "AST list not empty, pending %d, newlevel %d\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
		     lock->ast_pending, lock->ml.type);
		BUG();
	}
	if (lock->ast_pending)
		mlog(0, "%s: res %.*s, lock %u:%llu, AST getting flushed\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)));

	/* putting lock on list, add a ref */
	dlm_lock_get(lock);
	spin_lock(&lock->spinlock);

	/* check to see if this ast obsoletes the bast */
	if (dlm_should_cancel_bast(dlm, lock)) {
		mlog(0, "%s: res %.*s, lock %u:%llu, Cancelling BAST\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)));
		lock->bast_pending = 0;
		list_del_init(&lock->bast_list);
		lock->ml.highest_blocked = LKM_IVMODE;
		/* removing lock from list, remove a ref.  guaranteed
		 * this won't be the last ref because of the get above,
		 * so res->spinlock will not be taken here */
		dlm_lock_put(lock);
		/* free up the reserved bast that we are cancelling.
		 * guaranteed that this will not be the last reserved
		 * ast because *both* an ast and a bast were reserved
		 * to get to this point.  the res->spinlock will not be
		 * taken here */
		dlm_lockres_release_ast(dlm, res);
	}
	list_add_tail(&lock->ast_list, &dlm->pending_asts);
	lock->ast_pending = 1;
	spin_unlock(&lock->spinlock);
}