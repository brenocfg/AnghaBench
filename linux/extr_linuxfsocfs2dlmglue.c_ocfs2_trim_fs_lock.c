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
struct ocfs2_trim_fs_lvb {scalar_t__ lvb_version; int /*<<< orphan*/  lvb_trimlen; int /*<<< orphan*/  lvb_minlen; int /*<<< orphan*/  lvb_len; int /*<<< orphan*/  lvb_start; int /*<<< orphan*/  lvb_nodenum; int /*<<< orphan*/  lvb_success; } ;
struct ocfs2_trim_fs_info {int tf_valid; void* tf_trimlen; void* tf_minlen; void* tf_len; void* tf_start; int /*<<< orphan*/  tf_nodenum; int /*<<< orphan*/  tf_success; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_lksb; } ;
struct ocfs2_super {struct ocfs2_lock_res osb_trim_fs_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LKF_NOQUEUE ; 
 int /*<<< orphan*/  DLM_LOCK_EX ; 
 int EAGAIN ; 
 int EROFS ; 
 scalar_t__ OCFS2_TRIMFS_LVB_VERSION ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_cluster_lock (struct ocfs2_super*,struct ocfs2_lock_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ocfs2_trim_fs_lvb* ocfs2_dlm_lvb (int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_dlm_lvb_valid (int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_mount_local (struct ocfs2_super*) ; 

int ocfs2_trim_fs_lock(struct ocfs2_super *osb,
		       struct ocfs2_trim_fs_info *info, int trylock)
{
	int status;
	struct ocfs2_trim_fs_lvb *lvb;
	struct ocfs2_lock_res *lockres = &osb->osb_trim_fs_lockres;

	if (info)
		info->tf_valid = 0;

	if (ocfs2_is_hard_readonly(osb))
		return -EROFS;

	if (ocfs2_mount_local(osb))
		return 0;

	status = ocfs2_cluster_lock(osb, lockres, DLM_LOCK_EX,
				    trylock ? DLM_LKF_NOQUEUE : 0, 0);
	if (status < 0) {
		if (status != -EAGAIN)
			mlog_errno(status);
		return status;
	}

	if (info) {
		lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
		if (ocfs2_dlm_lvb_valid(&lockres->l_lksb) &&
		    lvb->lvb_version == OCFS2_TRIMFS_LVB_VERSION) {
			info->tf_valid = 1;
			info->tf_success = lvb->lvb_success;
			info->tf_nodenum = be32_to_cpu(lvb->lvb_nodenum);
			info->tf_start = be64_to_cpu(lvb->lvb_start);
			info->tf_len = be64_to_cpu(lvb->lvb_len);
			info->tf_minlen = be64_to_cpu(lvb->lvb_minlen);
			info->tf_trimlen = be64_to_cpu(lvb->lvb_trimlen);
		}
	}

	return status;
}