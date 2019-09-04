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
struct user_lock_res {scalar_t__ l_level; scalar_t__ l_requested; int /*<<< orphan*/  l_event; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_flags; int /*<<< orphan*/  l_blocking; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_namelen; int /*<<< orphan*/  l_lksb; } ;
struct ocfs2_dlm_lksb {int dummy; } ;

/* Variables and functions */
 scalar_t__ DLM_LOCK_IV ; 
 int /*<<< orphan*/  DLM_LOCK_NL ; 
 int /*<<< orphan*/  ML_BASTS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  USER_LOCK_ATTACHED ; 
 int /*<<< orphan*/  USER_LOCK_BLOCKED ; 
 int /*<<< orphan*/  USER_LOCK_BUSY ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_dlm_lock_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_highest_compat_lock_level (int /*<<< orphan*/ ) ; 
 struct user_lock_res* user_lksb_to_lock_res (struct ocfs2_dlm_lksb*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_ast(struct ocfs2_dlm_lksb *lksb)
{
	struct user_lock_res *lockres = user_lksb_to_lock_res(lksb);
	int status;

	mlog(ML_BASTS, "AST fired for lockres %.*s, level %d => %d\n",
	     lockres->l_namelen, lockres->l_name, lockres->l_level,
	     lockres->l_requested);

	spin_lock(&lockres->l_lock);

	status = ocfs2_dlm_lock_status(&lockres->l_lksb);
	if (status) {
		mlog(ML_ERROR, "lksb status value of %u on lockres %.*s\n",
		     status, lockres->l_namelen, lockres->l_name);
		spin_unlock(&lockres->l_lock);
		return;
	}

	mlog_bug_on_msg(lockres->l_requested == DLM_LOCK_IV,
			"Lockres %.*s, requested ivmode. flags 0x%x\n",
			lockres->l_namelen, lockres->l_name, lockres->l_flags);

	/* we're downconverting. */
	if (lockres->l_requested < lockres->l_level) {
		if (lockres->l_requested <=
		    user_highest_compat_lock_level(lockres->l_blocking)) {
			lockres->l_blocking = DLM_LOCK_NL;
			lockres->l_flags &= ~USER_LOCK_BLOCKED;
		}
	}

	lockres->l_level = lockres->l_requested;
	lockres->l_requested = DLM_LOCK_IV;
	lockres->l_flags |= USER_LOCK_ATTACHED;
	lockres->l_flags &= ~USER_LOCK_BUSY;

	spin_unlock(&lockres->l_lock);

	wake_up(&lockres->l_event);
}