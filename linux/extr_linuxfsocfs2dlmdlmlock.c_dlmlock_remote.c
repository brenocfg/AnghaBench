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
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dlm_lock_resource {scalar_t__ owner; int /*<<< orphan*/  wq; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  granted; TYPE_2__ lockname; int /*<<< orphan*/  state; int /*<<< orphan*/  blocked; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct dlm_lock {int lock_pending; int /*<<< orphan*/  list; TYPE_1__ ml; } ;
struct dlm_ctxt {scalar_t__ node_num; int /*<<< orphan*/  name; } ;
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;

/* Variables and functions */
 int DLM_DENIED ; 
 int /*<<< orphan*/  DLM_LOCK_RES_IN_PROGRESS ; 
 int DLM_NORMAL ; 
 int DLM_NOTQUEUED ; 
 int DLM_RECOVERING ; 
 int /*<<< orphan*/  __dlm_wait_on_lockres (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_error (int) ; 
 scalar_t__ dlm_is_recovery_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_lock_get (struct dlm_lock*) ; 
 int /*<<< orphan*/  dlm_lock_put (struct dlm_lock*) ; 
 int /*<<< orphan*/  dlm_lockres_calc_usage (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_revert_pending_lock (struct dlm_lock_resource*,struct dlm_lock*) ; 
 int dlm_send_remote_lock_request (struct dlm_ctxt*,struct dlm_lock_resource*,struct dlm_lock*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum dlm_status dlmlock_remote(struct dlm_ctxt *dlm,
				      struct dlm_lock_resource *res,
				      struct dlm_lock *lock, int flags)
{
	enum dlm_status status = DLM_DENIED;
	int lockres_changed = 1;

	mlog(0, "type=%d, lockres %.*s, flags = 0x%x\n",
	     lock->ml.type, res->lockname.len,
	     res->lockname.name, flags);

	/*
	 * Wait if resource is getting recovered, remastered, etc.
	 * If the resource was remastered and new owner is self, then exit.
	 */
	spin_lock(&res->spinlock);
	__dlm_wait_on_lockres(res);
	if (res->owner == dlm->node_num) {
		spin_unlock(&res->spinlock);
		return DLM_RECOVERING;
	}
	res->state |= DLM_LOCK_RES_IN_PROGRESS;

	/* add lock to local (secondary) queue */
	dlm_lock_get(lock);
	list_add_tail(&lock->list, &res->blocked);
	lock->lock_pending = 1;
	spin_unlock(&res->spinlock);

	/* spec seems to say that you will get DLM_NORMAL when the lock
	 * has been queued, meaning we need to wait for a reply here. */
	status = dlm_send_remote_lock_request(dlm, res, lock, flags);

	spin_lock(&res->spinlock);
	res->state &= ~DLM_LOCK_RES_IN_PROGRESS;
	lock->lock_pending = 0;
	if (status != DLM_NORMAL) {
		if (status == DLM_RECOVERING &&
		    dlm_is_recovery_lock(res->lockname.name,
					 res->lockname.len)) {
			/* recovery lock was mastered by dead node.
			 * we need to have calc_usage shoot down this
			 * lockres and completely remaster it. */
			mlog(0, "%s: recovery lock was owned by "
			     "dead node %u, remaster it now.\n",
			     dlm->name, res->owner);
		} else if (status != DLM_NOTQUEUED) {
			/*
			 * DO NOT call calc_usage, as this would unhash
			 * the remote lockres before we ever get to use
			 * it.  treat as if we never made any change to
			 * the lockres.
			 */
			lockres_changed = 0;
			dlm_error(status);
		}
		dlm_revert_pending_lock(res, lock);
		dlm_lock_put(lock);
	} else if (dlm_is_recovery_lock(res->lockname.name,
					res->lockname.len)) {
		/* special case for the $RECOVERY lock.
		 * there will never be an AST delivered to put
		 * this lock on the proper secondary queue
		 * (granted), so do it manually. */
		mlog(0, "%s: $RECOVERY lock for this node (%u) is "
		     "mastered by %u; got lock, manually granting (no ast)\n",
		     dlm->name, dlm->node_num, res->owner);
		list_move_tail(&lock->list, &res->granted);
	}
	spin_unlock(&res->spinlock);

	if (lockres_changed)
		dlm_lockres_calc_usage(dlm, res);

	wake_up(&res->wq);
	return status;
}