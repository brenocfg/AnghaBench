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
struct ocfs2_lock_res {int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_lksb; TYPE_1__* l_ops; int /*<<< orphan*/  l_level; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LKF_CONVERT ; 
 int /*<<< orphan*/  DLM_LKF_VALBLK ; 
 int LOCK_TYPE_USES_LVB ; 
 int /*<<< orphan*/  ML_BASTS ; 
 scalar_t__ OCFS2_LOCK_ID_MAX_LEN ; 
 int /*<<< orphan*/  lockres_clear_pending (struct ocfs2_lock_res*,unsigned int,struct ocfs2_super*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ocfs2_dlm_lock (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_log_dlm_error (char*,int,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_recover_from_dlm_error (struct ocfs2_lock_res*,int) ; 
 scalar_t__ ocfs2_userspace_stack (struct ocfs2_super*) ; 

__attribute__((used)) static int ocfs2_downconvert_lock(struct ocfs2_super *osb,
				  struct ocfs2_lock_res *lockres,
				  int new_level,
				  int lvb,
				  unsigned int generation)
{
	int ret;
	u32 dlm_flags = DLM_LKF_CONVERT;

	mlog(ML_BASTS, "lockres %s, level %d => %d\n", lockres->l_name,
	     lockres->l_level, new_level);

	/*
	 * On DLM_LKF_VALBLK, fsdlm behaves differently with o2cb. It always
	 * expects DLM_LKF_VALBLK being set if the LKB has LVB, so that
	 * we can recover correctly from node failure. Otherwise, we may get
	 * invalid LVB in LKB, but without DLM_SBF_VALNOTVALID being set.
	 */
	if (ocfs2_userspace_stack(osb) &&
	    lockres->l_ops->flags & LOCK_TYPE_USES_LVB)
		lvb = 1;

	if (lvb)
		dlm_flags |= DLM_LKF_VALBLK;

	ret = ocfs2_dlm_lock(osb->cconn,
			     new_level,
			     &lockres->l_lksb,
			     dlm_flags,
			     lockres->l_name,
			     OCFS2_LOCK_ID_MAX_LEN - 1);
	lockres_clear_pending(lockres, generation, osb);
	if (ret) {
		ocfs2_log_dlm_error("ocfs2_dlm_lock", ret, lockres);
		ocfs2_recover_from_dlm_error(lockres, 1);
		goto bail;
	}

	ret = 0;
bail:
	return ret;
}