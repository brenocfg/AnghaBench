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
struct ocfs2_super {int /*<<< orphan*/  slot_num; struct inode* sys_root_inode; int /*<<< orphan*/  system_dir_blkno; struct inode* root_inode; int /*<<< orphan*/  root_blkno; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EROFS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int OCFS2_FIRST_ONLINE_SYSTEM_INODE ; 
 int /*<<< orphan*/  OCFS2_FI_FLAG_SYSFILE ; 
 int OCFS2_LAST_GLOBAL_SYSTEM_INODE ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int,int /*<<< orphan*/ ) ; 
 struct inode* ocfs2_iget (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_is_soft_readonly (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_need_system_inode (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_release_system_inodes (struct ocfs2_super*) ; 

__attribute__((used)) static int ocfs2_init_global_system_inodes(struct ocfs2_super *osb)
{
	struct inode *new = NULL;
	int status = 0;
	int i;

	new = ocfs2_iget(osb, osb->root_blkno, OCFS2_FI_FLAG_SYSFILE, 0);
	if (IS_ERR(new)) {
		status = PTR_ERR(new);
		mlog_errno(status);
		goto bail;
	}
	osb->root_inode = new;

	new = ocfs2_iget(osb, osb->system_dir_blkno, OCFS2_FI_FLAG_SYSFILE, 0);
	if (IS_ERR(new)) {
		status = PTR_ERR(new);
		mlog_errno(status);
		goto bail;
	}
	osb->sys_root_inode = new;

	for (i = OCFS2_FIRST_ONLINE_SYSTEM_INODE;
	     i <= OCFS2_LAST_GLOBAL_SYSTEM_INODE; i++) {
		if (!ocfs2_need_system_inode(osb, i))
			continue;
		new = ocfs2_get_system_file_inode(osb, i, osb->slot_num);
		if (!new) {
			ocfs2_release_system_inodes(osb);
			status = ocfs2_is_soft_readonly(osb) ? -EROFS : -EINVAL;
			mlog_errno(status);
			mlog(ML_ERROR, "Unable to load system inode %d, "
			     "possibly corrupt fs?", i);
			goto bail;
		}
		// the array now has one ref, so drop this one
		iput(new);
	}

bail:
	if (status)
		mlog_errno(status);
	return status;
}