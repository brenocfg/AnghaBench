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
struct ocfs2_super {int /*<<< orphan*/  slot_num; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ORPHAN_DIR_SYSTEM_INODE ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 

__attribute__((used)) static int ocfs2_lookup_lock_orphan_dir(struct ocfs2_super *osb,
					struct inode **ret_orphan_dir,
					struct buffer_head **ret_orphan_dir_bh)
{
	struct inode *orphan_dir_inode;
	struct buffer_head *orphan_dir_bh = NULL;
	int ret = 0;

	orphan_dir_inode = ocfs2_get_system_file_inode(osb,
						       ORPHAN_DIR_SYSTEM_INODE,
						       osb->slot_num);
	if (!orphan_dir_inode) {
		ret = -ENOENT;
		mlog_errno(ret);
		return ret;
	}

	inode_lock(orphan_dir_inode);

	ret = ocfs2_inode_lock(orphan_dir_inode, &orphan_dir_bh, 1);
	if (ret < 0) {
		inode_unlock(orphan_dir_inode);
		iput(orphan_dir_inode);

		mlog_errno(ret);
		return ret;
	}

	*ret_orphan_dir = orphan_dir_inode;
	*ret_orphan_dir_bh = orphan_dir_bh;

	return 0;
}