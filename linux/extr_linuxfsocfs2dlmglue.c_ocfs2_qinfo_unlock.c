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
struct ocfs2_super {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dqi_sb; } ;
struct ocfs2_lock_res {int dummy; } ;
struct ocfs2_mem_dqinfo {TYPE_1__ dqi_gi; struct ocfs2_lock_res dqi_gqlock; } ;

/* Variables and functions */
 int DLM_LOCK_EX ; 
 int DLM_LOCK_PR ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_cluster_unlock (struct ocfs2_super*,struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_mount_local (struct ocfs2_super*) ; 

void ocfs2_qinfo_unlock(struct ocfs2_mem_dqinfo *oinfo, int ex)
{
	struct ocfs2_lock_res *lockres = &oinfo->dqi_gqlock;
	struct ocfs2_super *osb = OCFS2_SB(oinfo->dqi_gi.dqi_sb);
	int level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;

	if (!ocfs2_is_hard_readonly(osb) && !ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, lockres, level);
}