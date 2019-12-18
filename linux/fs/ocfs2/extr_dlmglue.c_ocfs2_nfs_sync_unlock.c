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
struct ocfs2_lock_res {int dummy; } ;
struct ocfs2_super {struct ocfs2_lock_res osb_nfs_sync_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  LKM_EXMODE ; 
 int /*<<< orphan*/  LKM_PRMODE ; 
 int /*<<< orphan*/  ocfs2_cluster_unlock (struct ocfs2_super*,struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_mount_local (struct ocfs2_super*) ; 

void ocfs2_nfs_sync_unlock(struct ocfs2_super *osb, int ex)
{
	struct ocfs2_lock_res *lockres = &osb->osb_nfs_sync_lockres;

	if (!ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, lockres,
				     ex ? LKM_EXMODE : LKM_PRMODE);
}