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
struct ocfs2_super {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int EAGAIN ; 
 int /*<<< orphan*/  JOURNAL_SYSTEM_INODE ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int OCFS2_META_LOCK_NOQUEUE ; 
 int OCFS2_META_LOCK_RECOVERY ; 
 int /*<<< orphan*/  SET_INODE_JOURNAL (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int) ; 
 int ocfs2_inode_lock_full (struct inode*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 

__attribute__((used)) static int ocfs2_trylock_journal(struct ocfs2_super *osb,
				 int slot_num)
{
	int status, flags;
	struct inode *inode = NULL;

	inode = ocfs2_get_system_file_inode(osb, JOURNAL_SYSTEM_INODE,
					    slot_num);
	if (inode == NULL) {
		mlog(ML_ERROR, "access error\n");
		status = -EACCES;
		goto bail;
	}
	if (is_bad_inode(inode)) {
		mlog(ML_ERROR, "access error (bad inode)\n");
		iput(inode);
		inode = NULL;
		status = -EACCES;
		goto bail;
	}
	SET_INODE_JOURNAL(inode);

	flags = OCFS2_META_LOCK_RECOVERY | OCFS2_META_LOCK_NOQUEUE;
	status = ocfs2_inode_lock_full(inode, NULL, 1, flags);
	if (status < 0) {
		if (status != -EAGAIN)
			mlog_errno(status);
		goto bail;
	}

	ocfs2_inode_unlock(inode, 1);
bail:
	iput(inode);

	return status;
}