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
struct user_lock_res {int l_flags; int /*<<< orphan*/  l_event; int /*<<< orphan*/  l_lock; void* l_requested; void* l_level; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_namelen; } ;
struct ocfs2_dlm_lksb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_CANCELGRANT ; 
 void* DLM_LOCK_IV ; 
 int /*<<< orphan*/  ML_BASTS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int USER_LOCK_BLOCKED ; 
 int USER_LOCK_BUSY ; 
 int USER_LOCK_IN_CANCEL ; 
 int USER_LOCK_IN_TEARDOWN ; 
 int /*<<< orphan*/  __user_dlm_queue_lockres (struct user_lock_res*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct user_lock_res* user_lksb_to_lock_res (struct ocfs2_dlm_lksb*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_unlock_ast(struct ocfs2_dlm_lksb *lksb, int status)
{
	struct user_lock_res *lockres = user_lksb_to_lock_res(lksb);

	mlog(ML_BASTS, "UNLOCK AST fired for lockres %.*s, flags 0x%x\n",
	     lockres->l_namelen, lockres->l_name, lockres->l_flags);

	if (status)
		mlog(ML_ERROR, "dlm returns status %d\n", status);

	spin_lock(&lockres->l_lock);
	/* The teardown flag gets set early during the unlock process,
	 * so test the cancel flag to make sure that this ast isn't
	 * for a concurrent cancel. */
	if (lockres->l_flags & USER_LOCK_IN_TEARDOWN
	    && !(lockres->l_flags & USER_LOCK_IN_CANCEL)) {
		lockres->l_level = DLM_LOCK_IV;
	} else if (status == DLM_CANCELGRANT) {
		/* We tried to cancel a convert request, but it was
		 * already granted. Don't clear the busy flag - the
		 * ast should've done this already. */
		BUG_ON(!(lockres->l_flags & USER_LOCK_IN_CANCEL));
		lockres->l_flags &= ~USER_LOCK_IN_CANCEL;
		goto out_noclear;
	} else {
		BUG_ON(!(lockres->l_flags & USER_LOCK_IN_CANCEL));
		/* Cancel succeeded, we want to re-queue */
		lockres->l_requested = DLM_LOCK_IV; /* cancel an
						    * upconvert
						    * request. */
		lockres->l_flags &= ~USER_LOCK_IN_CANCEL;
		/* we want the unblock thread to look at it again
		 * now. */
		if (lockres->l_flags & USER_LOCK_BLOCKED)
			__user_dlm_queue_lockres(lockres);
	}

	lockres->l_flags &= ~USER_LOCK_BUSY;
out_noclear:
	spin_unlock(&lockres->l_lock);

	wake_up(&lockres->l_event);
}