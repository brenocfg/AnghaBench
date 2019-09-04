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
struct ocfs2_super {scalar_t__ dc_task; int /*<<< orphan*/  dc_task_lock; int /*<<< orphan*/  blocked_lock_count; } ;
struct ocfs2_mask_waiter {int dummy; } ;
struct ocfs2_lock_res {int l_flags; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_name; TYPE_1__* l_ops; int /*<<< orphan*/  l_blocked_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  post_unlock; } ;

/* Variables and functions */
 int OCFS2_LOCK_FREEING ; 
 int OCFS2_LOCK_QUEUED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockres_add_mask_waiter (struct ocfs2_lock_res*,struct ocfs2_mask_waiter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_init_mask_waiter (struct ocfs2_mask_waiter*) ; 
 int /*<<< orphan*/  ocfs2_process_blocked_lock (struct ocfs2_super*,struct ocfs2_lock_res*) ; 
 int ocfs2_wait_for_mask (struct ocfs2_mask_waiter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ocfs2_mark_lockres_freeing(struct ocfs2_super *osb,
				struct ocfs2_lock_res *lockres)
{
	int status;
	struct ocfs2_mask_waiter mw;
	unsigned long flags, flags2;

	ocfs2_init_mask_waiter(&mw);

	spin_lock_irqsave(&lockres->l_lock, flags);
	lockres->l_flags |= OCFS2_LOCK_FREEING;
	if (lockres->l_flags & OCFS2_LOCK_QUEUED && current == osb->dc_task) {
		/*
		 * We know the downconvert is queued but not in progress
		 * because we are the downconvert thread and processing
		 * different lock. So we can just remove the lock from the
		 * queue. This is not only an optimization but also a way
		 * to avoid the following deadlock:
		 *   ocfs2_dentry_post_unlock()
		 *     ocfs2_dentry_lock_put()
		 *       ocfs2_drop_dentry_lock()
		 *         iput()
		 *           ocfs2_evict_inode()
		 *             ocfs2_clear_inode()
		 *               ocfs2_mark_lockres_freeing()
		 *                 ... blocks waiting for OCFS2_LOCK_QUEUED
		 *                 since we are the downconvert thread which
		 *                 should clear the flag.
		 */
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		spin_lock_irqsave(&osb->dc_task_lock, flags2);
		list_del_init(&lockres->l_blocked_list);
		osb->blocked_lock_count--;
		spin_unlock_irqrestore(&osb->dc_task_lock, flags2);
		/*
		 * Warn if we recurse into another post_unlock call.  Strictly
		 * speaking it isn't a problem but we need to be careful if
		 * that happens (stack overflow, deadlocks, ...) so warn if
		 * ocfs2 grows a path for which this can happen.
		 */
		WARN_ON_ONCE(lockres->l_ops->post_unlock);
		/* Since the lock is freeing we don't do much in the fn below */
		ocfs2_process_blocked_lock(osb, lockres);
		return;
	}
	while (lockres->l_flags & OCFS2_LOCK_QUEUED) {
		lockres_add_mask_waiter(lockres, &mw, OCFS2_LOCK_QUEUED, 0);
		spin_unlock_irqrestore(&lockres->l_lock, flags);

		mlog(0, "Waiting on lockres %s\n", lockres->l_name);

		status = ocfs2_wait_for_mask(&mw);
		if (status)
			mlog_errno(status);

		spin_lock_irqsave(&lockres->l_lock, flags);
	}
	spin_unlock_irqrestore(&lockres->l_lock, flags);
}