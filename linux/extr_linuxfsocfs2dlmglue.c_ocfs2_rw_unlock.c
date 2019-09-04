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
struct ocfs2_lock_res {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {scalar_t__ ip_blkno; struct ocfs2_lock_res ip_rw_lockres; } ;

/* Variables and functions */
 int DLM_LOCK_EX ; 
 int DLM_LOCK_PR ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,char*) ; 
 int /*<<< orphan*/  ocfs2_cluster_unlock (struct ocfs2_super*,struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  ocfs2_mount_local (struct ocfs2_super*) ; 

void ocfs2_rw_unlock(struct inode *inode, int write)
{
	int level = write ? DLM_LOCK_EX : DLM_LOCK_PR;
	struct ocfs2_lock_res *lockres = &OCFS2_I(inode)->ip_rw_lockres;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	mlog(0, "inode %llu drop %s RW lock\n",
	     (unsigned long long)OCFS2_I(inode)->ip_blkno,
	     write ? "EXMODE" : "PRMODE");

	if (!ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, lockres, level);
}