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
struct ocfs2_super {int dummy; } ;
struct ocfs2_mask_waiter {int dummy; } ;
struct ocfs2_lock_res {int l_flags; int l_level; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_action; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int OCFS2_LOCK_BUSY ; 
 int /*<<< orphan*/  lockres_add_mask_waiter (struct ocfs2_lock_res*,struct ocfs2_mask_waiter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_cancel_convert (struct ocfs2_super*,struct ocfs2_lock_res*) ; 
 struct ocfs2_super* ocfs2_get_lockres_osb (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_init_mask_waiter (struct ocfs2_mask_waiter*) ; 
 int ocfs2_prepare_cancel_convert (struct ocfs2_super*,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_wait_for_mask (struct ocfs2_mask_waiter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ocfs2_flock_handle_signal(struct ocfs2_lock_res *lockres,
				     int level)
{
	int ret;
	struct ocfs2_super *osb = ocfs2_get_lockres_osb(lockres);
	unsigned long flags;
	struct ocfs2_mask_waiter mw;

	ocfs2_init_mask_waiter(&mw);

retry_cancel:
	spin_lock_irqsave(&lockres->l_lock, flags);
	if (lockres->l_flags & OCFS2_LOCK_BUSY) {
		ret = ocfs2_prepare_cancel_convert(osb, lockres);
		if (ret) {
			spin_unlock_irqrestore(&lockres->l_lock, flags);
			ret = ocfs2_cancel_convert(osb, lockres);
			if (ret < 0) {
				mlog_errno(ret);
				goto out;
			}
			goto retry_cancel;
		}
		lockres_add_mask_waiter(lockres, &mw, OCFS2_LOCK_BUSY, 0);
		spin_unlock_irqrestore(&lockres->l_lock, flags);

		ocfs2_wait_for_mask(&mw);
		goto retry_cancel;
	}

	ret = -ERESTARTSYS;
	/*
	 * We may still have gotten the lock, in which case there's no
	 * point to restarting the syscall.
	 */
	if (lockres->l_level == level)
		ret = 0;

	mlog(0, "Cancel returning %d. flags: 0x%lx, level: %d, act: %d\n", ret,
	     lockres->l_flags, lockres->l_level, lockres->l_action);

	spin_unlock_irqrestore(&lockres->l_lock, flags);

out:
	return ret;
}