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
struct ocfs2_trim_fs_lvb {void* lvb_trimlen; void* lvb_minlen; void* lvb_len; void* lvb_start; int /*<<< orphan*/  lvb_nodenum; int /*<<< orphan*/  lvb_success; int /*<<< orphan*/  lvb_version; } ;
struct ocfs2_trim_fs_info {int /*<<< orphan*/  tf_trimlen; int /*<<< orphan*/  tf_minlen; int /*<<< orphan*/  tf_len; int /*<<< orphan*/  tf_start; int /*<<< orphan*/  tf_nodenum; int /*<<< orphan*/  tf_success; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_lksb; } ;
struct ocfs2_super {struct ocfs2_lock_res osb_trim_fs_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_EX ; 
 int /*<<< orphan*/  OCFS2_TRIMFS_LVB_VERSION ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_cluster_unlock (struct ocfs2_super*,struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 struct ocfs2_trim_fs_lvb* ocfs2_dlm_lvb (int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_mount_local (struct ocfs2_super*) ; 

void ocfs2_trim_fs_unlock(struct ocfs2_super *osb,
			  struct ocfs2_trim_fs_info *info)
{
	struct ocfs2_trim_fs_lvb *lvb;
	struct ocfs2_lock_res *lockres = &osb->osb_trim_fs_lockres;

	if (ocfs2_mount_local(osb))
		return;

	if (info) {
		lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
		lvb->lvb_version = OCFS2_TRIMFS_LVB_VERSION;
		lvb->lvb_success = info->tf_success;
		lvb->lvb_nodenum = cpu_to_be32(info->tf_nodenum);
		lvb->lvb_start = cpu_to_be64(info->tf_start);
		lvb->lvb_len = cpu_to_be64(info->tf_len);
		lvb->lvb_minlen = cpu_to_be64(info->tf_minlen);
		lvb->lvb_trimlen = cpu_to_be64(info->tf_trimlen);
	}

	ocfs2_cluster_unlock(osb, lockres, DLM_LOCK_EX);
}