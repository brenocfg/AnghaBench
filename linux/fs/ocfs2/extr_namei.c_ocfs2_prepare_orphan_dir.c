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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_dir_lookup_result {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int __ocfs2_prepare_orphan_dir (struct inode*,struct buffer_head*,int /*<<< orphan*/ ,char*,struct ocfs2_dir_lookup_result*,int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_lookup_lock_orphan_dir (struct ocfs2_super*,struct inode**,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_prepare_orphan_dir(struct ocfs2_super *osb,
				    struct inode **ret_orphan_dir,
				    u64 blkno,
				    char *name,
				    struct ocfs2_dir_lookup_result *lookup,
				    bool dio)
{
	struct inode *orphan_dir_inode = NULL;
	struct buffer_head *orphan_dir_bh = NULL;
	int ret = 0;

	ret = ocfs2_lookup_lock_orphan_dir(osb, &orphan_dir_inode,
					   &orphan_dir_bh);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	ret = __ocfs2_prepare_orphan_dir(orphan_dir_inode, orphan_dir_bh,
					 blkno, name, lookup, dio);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	*ret_orphan_dir = orphan_dir_inode;

out:
	brelse(orphan_dir_bh);

	if (ret) {
		ocfs2_inode_unlock(orphan_dir_inode, 1);
		inode_unlock(orphan_dir_inode);
		iput(orphan_dir_inode);
	}

	if (ret)
		mlog_errno(ret);
	return ret;
}