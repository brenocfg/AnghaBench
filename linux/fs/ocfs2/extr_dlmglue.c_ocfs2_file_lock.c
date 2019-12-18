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
struct ocfs2_super {int /*<<< orphan*/  cconn; } ;
struct ocfs2_mask_waiter {int dummy; } ;
struct ocfs2_lock_res {int l_flags; int l_level; int l_requested; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_lksb; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_action; } ;
struct ocfs2_file_private {struct ocfs2_lock_res fp_flock; } ;
struct file {TYPE_2__* f_mapping; struct ocfs2_file_private* private_data; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int DLM_LKF_CONVERT ; 
 unsigned int DLM_LKF_NOQUEUE ; 
 int DLM_LOCK_EX ; 
 int DLM_LOCK_NL ; 
 int DLM_LOCK_PR ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_AST_CONVERT ; 
 int OCFS2_LOCK_ATTACHED ; 
 int OCFS2_LOCK_BUSY ; 
 scalar_t__ OCFS2_LOCK_ID_MAX_LEN ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockres_add_mask_waiter (struct ocfs2_lock_res*,struct ocfs2_mask_waiter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockres_or_flags (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  lockres_remove_mask_waiter (struct ocfs2_lock_res*,struct ocfs2_mask_waiter*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_dlm_lock (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 
 int ocfs2_flock_handle_signal (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  ocfs2_init_mask_waiter (struct ocfs2_mask_waiter*) ; 
 int ocfs2_lock_create (struct ocfs2_super*,struct ocfs2_lock_res*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_log_dlm_error (char*,int,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_recover_from_dlm_error (struct ocfs2_lock_res*,int) ; 
 int ocfs2_wait_for_mask (struct ocfs2_mask_waiter*) ; 
 int ocfs2_wait_for_mask_interruptible (struct ocfs2_mask_waiter*,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ocfs2_file_lock(struct file *file, int ex, int trylock)
{
	int ret, level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	unsigned int lkm_flags = trylock ? DLM_LKF_NOQUEUE : 0;
	unsigned long flags;
	struct ocfs2_file_private *fp = file->private_data;
	struct ocfs2_lock_res *lockres = &fp->fp_flock;
	struct ocfs2_super *osb = OCFS2_SB(file->f_mapping->host->i_sb);
	struct ocfs2_mask_waiter mw;

	ocfs2_init_mask_waiter(&mw);

	if ((lockres->l_flags & OCFS2_LOCK_BUSY) ||
	    (lockres->l_level > DLM_LOCK_NL)) {
		mlog(ML_ERROR,
		     "File lock \"%s\" has busy or locked state: flags: 0x%lx, "
		     "level: %u\n", lockres->l_name, lockres->l_flags,
		     lockres->l_level);
		return -EINVAL;
	}

	spin_lock_irqsave(&lockres->l_lock, flags);
	if (!(lockres->l_flags & OCFS2_LOCK_ATTACHED)) {
		lockres_add_mask_waiter(lockres, &mw, OCFS2_LOCK_BUSY, 0);
		spin_unlock_irqrestore(&lockres->l_lock, flags);

		/*
		 * Get the lock at NLMODE to start - that way we
		 * can cancel the upconvert request if need be.
		 */
		ret = ocfs2_lock_create(osb, lockres, DLM_LOCK_NL, 0);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}

		ret = ocfs2_wait_for_mask(&mw);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
		spin_lock_irqsave(&lockres->l_lock, flags);
	}

	lockres->l_action = OCFS2_AST_CONVERT;
	lkm_flags |= DLM_LKF_CONVERT;
	lockres->l_requested = level;
	lockres_or_flags(lockres, OCFS2_LOCK_BUSY);

	lockres_add_mask_waiter(lockres, &mw, OCFS2_LOCK_BUSY, 0);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	ret = ocfs2_dlm_lock(osb->cconn, level, &lockres->l_lksb, lkm_flags,
			     lockres->l_name, OCFS2_LOCK_ID_MAX_LEN - 1);
	if (ret) {
		if (!trylock || (ret != -EAGAIN)) {
			ocfs2_log_dlm_error("ocfs2_dlm_lock", ret, lockres);
			ret = -EINVAL;
		}

		ocfs2_recover_from_dlm_error(lockres, 1);
		lockres_remove_mask_waiter(lockres, &mw);
		goto out;
	}

	ret = ocfs2_wait_for_mask_interruptible(&mw, lockres);
	if (ret == -ERESTARTSYS) {
		/*
		 * Userspace can cause deadlock itself with
		 * flock(). Current behavior locally is to allow the
		 * deadlock, but abort the system call if a signal is
		 * received. We follow this example, otherwise a
		 * poorly written program could sit in kernel until
		 * reboot.
		 *
		 * Handling this is a bit more complicated for Ocfs2
		 * though. We can't exit this function with an
		 * outstanding lock request, so a cancel convert is
		 * required. We intentionally overwrite 'ret' - if the
		 * cancel fails and the lock was granted, it's easier
		 * to just bubble success back up to the user.
		 */
		ret = ocfs2_flock_handle_signal(lockres, level);
	} else if (!ret && (level > lockres->l_level)) {
		/* Trylock failed asynchronously */
		BUG_ON(!trylock);
		ret = -EAGAIN;
	}

out:

	mlog(0, "Lock: \"%s\" ex: %d, trylock: %d, returns: %d\n",
	     lockres->l_name, ex, trylock, ret);
	return ret;
}