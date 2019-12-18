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
struct vfsmount {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_should_update_atime (struct inode*,struct vfsmount*) ; 
 int ocfs2_try_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_update_inode_atime (struct inode*,struct buffer_head*) ; 

int ocfs2_inode_lock_atime(struct inode *inode,
			  struct vfsmount *vfsmnt,
			  int *level, int wait)
{
	int ret;

	if (wait)
		ret = ocfs2_inode_lock(inode, NULL, 0);
	else
		ret = ocfs2_try_inode_lock(inode, NULL, 0);

	if (ret < 0) {
		if (ret != -EAGAIN)
			mlog_errno(ret);
		return ret;
	}

	/*
	 * If we should update atime, we will get EX lock,
	 * otherwise we just get PR lock.
	 */
	if (ocfs2_should_update_atime(inode, vfsmnt)) {
		struct buffer_head *bh = NULL;

		ocfs2_inode_unlock(inode, 0);
		if (wait)
			ret = ocfs2_inode_lock(inode, &bh, 1);
		else
			ret = ocfs2_try_inode_lock(inode, &bh, 1);

		if (ret < 0) {
			if (ret != -EAGAIN)
				mlog_errno(ret);
			return ret;
		}
		*level = 1;
		if (ocfs2_should_update_atime(inode, vfsmnt))
			ocfs2_update_inode_atime(inode, bh);
		brelse(bh);
	} else
		*level = 0;

	return ret;
}