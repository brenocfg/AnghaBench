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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int /*<<< orphan*/  cconn; } ;
struct ocfs2_lock_res {int l_flags; int l_name; scalar_t__ l_action; scalar_t__ l_level; int /*<<< orphan*/  l_lksb; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_unlock_action; TYPE_1__* l_ops; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  (* set_lvb ) (struct ocfs2_lock_res*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DLM_LKF_VALBLK ; 
 scalar_t__ DLM_LOCK_EX ; 
 int LOCK_TYPE_USES_LVB ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ OCFS2_AST_INVALID ; 
 int OCFS2_LOCK_ATTACHED ; 
 int OCFS2_LOCK_BLOCKED ; 
 int OCFS2_LOCK_BUSY ; 
 int OCFS2_LOCK_FREEING ; 
 int OCFS2_LOCK_INITIALIZED ; 
 int OCFS2_LOCK_NEEDS_REFRESH ; 
 int /*<<< orphan*/  OCFS2_UNLOCK_DROP_LOCK ; 
 int /*<<< orphan*/  lockres_clear_flags (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  lockres_or_flags (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,int,int) ; 
 int /*<<< orphan*/  ocfs2_dlm_dump_lksb (int /*<<< orphan*/ *) ; 
 int ocfs2_dlm_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_log_dlm_error (char*,int,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_wait_on_busy_lock (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ocfs2_lock_res*) ; 

__attribute__((used)) static int ocfs2_drop_lock(struct ocfs2_super *osb,
			   struct ocfs2_lock_res *lockres)
{
	int ret;
	unsigned long flags;
	u32 lkm_flags = 0;

	/* We didn't get anywhere near actually using this lockres. */
	if (!(lockres->l_flags & OCFS2_LOCK_INITIALIZED))
		goto out;

	if (lockres->l_ops->flags & LOCK_TYPE_USES_LVB)
		lkm_flags |= DLM_LKF_VALBLK;

	spin_lock_irqsave(&lockres->l_lock, flags);

	mlog_bug_on_msg(!(lockres->l_flags & OCFS2_LOCK_FREEING),
			"lockres %s, flags 0x%lx\n",
			lockres->l_name, lockres->l_flags);

	while (lockres->l_flags & OCFS2_LOCK_BUSY) {
		mlog(0, "waiting on busy lock \"%s\": flags = %lx, action = "
		     "%u, unlock_action = %u\n",
		     lockres->l_name, lockres->l_flags, lockres->l_action,
		     lockres->l_unlock_action);

		spin_unlock_irqrestore(&lockres->l_lock, flags);

		/* XXX: Today we just wait on any busy
		 * locks... Perhaps we need to cancel converts in the
		 * future? */
		ocfs2_wait_on_busy_lock(lockres);

		spin_lock_irqsave(&lockres->l_lock, flags);
	}

	if (lockres->l_ops->flags & LOCK_TYPE_USES_LVB) {
		if (lockres->l_flags & OCFS2_LOCK_ATTACHED &&
		    lockres->l_level == DLM_LOCK_EX &&
		    !(lockres->l_flags & OCFS2_LOCK_NEEDS_REFRESH))
			lockres->l_ops->set_lvb(lockres);
	}

	if (lockres->l_flags & OCFS2_LOCK_BUSY)
		mlog(ML_ERROR, "destroying busy lock: \"%s\"\n",
		     lockres->l_name);
	if (lockres->l_flags & OCFS2_LOCK_BLOCKED)
		mlog(0, "destroying blocked lock: \"%s\"\n", lockres->l_name);

	if (!(lockres->l_flags & OCFS2_LOCK_ATTACHED)) {
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		goto out;
	}

	lockres_clear_flags(lockres, OCFS2_LOCK_ATTACHED);

	/* make sure we never get here while waiting for an ast to
	 * fire. */
	BUG_ON(lockres->l_action != OCFS2_AST_INVALID);

	/* is this necessary? */
	lockres_or_flags(lockres, OCFS2_LOCK_BUSY);
	lockres->l_unlock_action = OCFS2_UNLOCK_DROP_LOCK;
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	mlog(0, "lock %s\n", lockres->l_name);

	ret = ocfs2_dlm_unlock(osb->cconn, &lockres->l_lksb, lkm_flags);
	if (ret) {
		ocfs2_log_dlm_error("ocfs2_dlm_unlock", ret, lockres);
		mlog(ML_ERROR, "lockres flags: %lu\n", lockres->l_flags);
		ocfs2_dlm_dump_lksb(&lockres->l_lksb);
		BUG();
	}
	mlog(0, "lock %s, successful return from ocfs2_dlm_unlock\n",
	     lockres->l_name);

	ocfs2_wait_on_busy_lock(lockres);
out:
	return 0;
}