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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct dentry {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int ip_flags; int ip_dyn_features; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I_MUTEX_CHILD ; 
 int OCFS2_HAS_XATTR_FL ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_SYSTEM_FILE ; 
 int /*<<< orphan*/  OI_LS_REFLINK_TARGET ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int filemap_fdatawait (int /*<<< orphan*/ ) ; 
 int filemap_fdatawrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_attach_refcount_tree (struct inode*,struct buffer_head*) ; 
 int ocfs2_complete_reflink (struct inode*,struct buffer_head*,struct inode*,struct buffer_head*,int) ; 
 int ocfs2_create_reflink_node (struct inode*,struct buffer_head*,struct inode*,struct buffer_head*,int) ; 
 int ocfs2_inode_lock_nested (struct inode*,struct buffer_head**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_reflink_xattrs (struct inode*,struct buffer_head*,struct inode*,struct buffer_head*,int) ; 

__attribute__((used)) static int __ocfs2_reflink(struct dentry *old_dentry,
			   struct buffer_head *old_bh,
			   struct inode *new_inode,
			   bool preserve)
{
	int ret;
	struct inode *inode = d_inode(old_dentry);
	struct buffer_head *new_bh = NULL;

	if (OCFS2_I(inode)->ip_flags & OCFS2_INODE_SYSTEM_FILE) {
		ret = -EINVAL;
		mlog_errno(ret);
		goto out;
	}

	ret = filemap_fdatawrite(inode->i_mapping);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_attach_refcount_tree(inode, old_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	inode_lock_nested(new_inode, I_MUTEX_CHILD);
	ret = ocfs2_inode_lock_nested(new_inode, &new_bh, 1,
				      OI_LS_REFLINK_TARGET);
	if (ret) {
		mlog_errno(ret);
		goto out_unlock;
	}

	ret = ocfs2_create_reflink_node(inode, old_bh,
					new_inode, new_bh, preserve);
	if (ret) {
		mlog_errno(ret);
		goto inode_unlock;
	}

	if (OCFS2_I(inode)->ip_dyn_features & OCFS2_HAS_XATTR_FL) {
		ret = ocfs2_reflink_xattrs(inode, old_bh,
					   new_inode, new_bh,
					   preserve);
		if (ret) {
			mlog_errno(ret);
			goto inode_unlock;
		}
	}

	ret = ocfs2_complete_reflink(inode, old_bh,
				     new_inode, new_bh, preserve);
	if (ret)
		mlog_errno(ret);

inode_unlock:
	ocfs2_inode_unlock(new_inode, 1);
	brelse(new_bh);
out_unlock:
	inode_unlock(new_inode);
out:
	if (!ret) {
		ret = filemap_fdatawait(inode->i_mapping);
		if (ret)
			mlog_errno(ret);
	}
	return ret;
}