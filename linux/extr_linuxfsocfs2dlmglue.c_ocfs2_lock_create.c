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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int /*<<< orphan*/  cconn; } ;
struct ocfs2_lock_res {int l_flags; int l_requested; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_lksb; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_AST_ATTACH ; 
 int OCFS2_LOCK_ATTACHED ; 
 int OCFS2_LOCK_BUSY ; 
 scalar_t__ OCFS2_LOCK_ID_MAX_LEN ; 
 int /*<<< orphan*/  lockres_clear_pending (struct ocfs2_lock_res*,unsigned int,struct ocfs2_super*) ; 
 int /*<<< orphan*/  lockres_or_flags (struct ocfs2_lock_res*,int) ; 
 unsigned int lockres_set_pending (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int ocfs2_dlm_lock (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_log_dlm_error (char*,int,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_recover_from_dlm_error (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ocfs2_lock_create(struct ocfs2_super *osb,
			     struct ocfs2_lock_res *lockres,
			     int level,
			     u32 dlm_flags)
{
	int ret = 0;
	unsigned long flags;
	unsigned int gen;

	mlog(0, "lock %s, level = %d, flags = %u\n", lockres->l_name, level,
	     dlm_flags);

	spin_lock_irqsave(&lockres->l_lock, flags);
	if ((lockres->l_flags & OCFS2_LOCK_ATTACHED) ||
	    (lockres->l_flags & OCFS2_LOCK_BUSY)) {
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		goto bail;
	}

	lockres->l_action = OCFS2_AST_ATTACH;
	lockres->l_requested = level;
	lockres_or_flags(lockres, OCFS2_LOCK_BUSY);
	gen = lockres_set_pending(lockres);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	ret = ocfs2_dlm_lock(osb->cconn,
			     level,
			     &lockres->l_lksb,
			     dlm_flags,
			     lockres->l_name,
			     OCFS2_LOCK_ID_MAX_LEN - 1);
	lockres_clear_pending(lockres, gen, osb);
	if (ret) {
		ocfs2_log_dlm_error("ocfs2_dlm_lock", ret, lockres);
		ocfs2_recover_from_dlm_error(lockres, 1);
	}

	mlog(0, "lock %s, return from ocfs2_dlm_lock\n", lockres->l_name);

bail:
	return ret;
}