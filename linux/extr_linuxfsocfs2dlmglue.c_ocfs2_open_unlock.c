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
struct ocfs2_lock_res {scalar_t__ l_ex_holders; scalar_t__ l_ro_holders; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {scalar_t__ ip_blkno; struct ocfs2_lock_res ip_open_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_EX ; 
 int /*<<< orphan*/  DLM_LOCK_PR ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  ocfs2_cluster_unlock (struct ocfs2_super*,struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_mount_local (struct ocfs2_super*) ; 

void ocfs2_open_unlock(struct inode *inode)
{
	struct ocfs2_lock_res *lockres = &OCFS2_I(inode)->ip_open_lockres;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	mlog(0, "inode %llu drop open lock\n",
	     (unsigned long long)OCFS2_I(inode)->ip_blkno);

	if (ocfs2_mount_local(osb))
		goto out;

	if(lockres->l_ro_holders)
		ocfs2_cluster_unlock(osb, lockres, DLM_LOCK_PR);
	if(lockres->l_ex_holders)
		ocfs2_cluster_unlock(osb, lockres, DLM_LOCK_EX);

out:
	return;
}