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
struct ocfs2_super {int dummy; } ;
struct ocfs2_mask_waiter {int dummy; } ;
struct ocfs2_lock_res {int l_flags; scalar_t__ l_level; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_blocking; int /*<<< orphan*/  l_action; int /*<<< orphan*/  l_name; } ;
struct ocfs2_file_private {struct ocfs2_lock_res fp_flock; } ;
struct file {TYPE_2__* f_mapping; struct ocfs2_file_private* private_data; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_EX ; 
 scalar_t__ DLM_LOCK_NL ; 
 int OCFS2_LOCK_ATTACHED ; 
 int /*<<< orphan*/  OCFS2_LOCK_BLOCKED ; 
 int /*<<< orphan*/  OCFS2_LOCK_BUSY ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockres_add_mask_waiter (struct ocfs2_lock_res*,struct ocfs2_mask_waiter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockres_or_flags (struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_downconvert_lock (struct ocfs2_super*,struct ocfs2_lock_res*,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_init_mask_waiter (struct ocfs2_mask_waiter*) ; 
 unsigned int ocfs2_prepare_downconvert (struct ocfs2_lock_res*,scalar_t__) ; 
 int ocfs2_wait_for_mask (struct ocfs2_mask_waiter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ocfs2_file_unlock(struct file *file)
{
	int ret;
	unsigned int gen;
	unsigned long flags;
	struct ocfs2_file_private *fp = file->private_data;
	struct ocfs2_lock_res *lockres = &fp->fp_flock;
	struct ocfs2_super *osb = OCFS2_SB(file->f_mapping->host->i_sb);
	struct ocfs2_mask_waiter mw;

	ocfs2_init_mask_waiter(&mw);

	if (!(lockres->l_flags & OCFS2_LOCK_ATTACHED))
		return;

	if (lockres->l_level == DLM_LOCK_NL)
		return;

	mlog(0, "Unlock: \"%s\" flags: 0x%lx, level: %d, act: %d\n",
	     lockres->l_name, lockres->l_flags, lockres->l_level,
	     lockres->l_action);

	spin_lock_irqsave(&lockres->l_lock, flags);
	/*
	 * Fake a blocking ast for the downconvert code.
	 */
	lockres_or_flags(lockres, OCFS2_LOCK_BLOCKED);
	lockres->l_blocking = DLM_LOCK_EX;

	gen = ocfs2_prepare_downconvert(lockres, DLM_LOCK_NL);
	lockres_add_mask_waiter(lockres, &mw, OCFS2_LOCK_BUSY, 0);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	ret = ocfs2_downconvert_lock(osb, lockres, DLM_LOCK_NL, 0, gen);
	if (ret) {
		mlog_errno(ret);
		return;
	}

	ret = ocfs2_wait_for_mask(&mw);
	if (ret)
		mlog_errno(ret);
}