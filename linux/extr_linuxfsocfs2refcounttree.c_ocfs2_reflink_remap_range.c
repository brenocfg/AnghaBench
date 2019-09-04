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
typedef  scalar_t__ u64 ;
struct ocfs2_super {int dummy; } ;
struct inode {int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int ip_flags; int /*<<< orphan*/  ip_alloc_sem; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EROFS ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_SYSTEM_FILE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_ALIGN (scalar_t__) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_extent_map_trunc (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_is_soft_readonly (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_refcount_tree (struct ocfs2_super*) ; 
 int ocfs2_reflink_inodes_lock (struct inode*,struct buffer_head**,struct inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_reflink_inodes_unlock (struct inode*,struct buffer_head*,struct inode*,struct buffer_head*) ; 
 int ocfs2_reflink_remap_blocks (struct inode*,struct buffer_head*,scalar_t__,struct inode*,struct buffer_head*,scalar_t__,scalar_t__) ; 
 int ocfs2_reflink_update_dest (struct inode*,struct buffer_head*,scalar_t__) ; 
 int /*<<< orphan*/  truncate_inode_pages_range (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int vfs_clone_file_prep_inodes (struct inode*,scalar_t__,struct inode*,scalar_t__,scalar_t__*,int) ; 

int ocfs2_reflink_remap_range(struct file *file_in,
			      loff_t pos_in,
			      struct file *file_out,
			      loff_t pos_out,
			      u64 len,
			      bool is_dedupe)
{
	struct inode *inode_in = file_inode(file_in);
	struct inode *inode_out = file_inode(file_out);
	struct ocfs2_super *osb = OCFS2_SB(inode_in->i_sb);
	struct buffer_head *in_bh = NULL, *out_bh = NULL;
	bool same_inode = (inode_in == inode_out);
	ssize_t ret;

	if (!ocfs2_refcount_tree(osb))
		return -EOPNOTSUPP;
	if (ocfs2_is_hard_readonly(osb) || ocfs2_is_soft_readonly(osb))
		return -EROFS;

	/* Lock both files against IO */
	ret = ocfs2_reflink_inodes_lock(inode_in, &in_bh, inode_out, &out_bh);
	if (ret)
		return ret;

	/* Check file eligibility and prepare for block sharing. */
	ret = -EINVAL;
	if ((OCFS2_I(inode_in)->ip_flags & OCFS2_INODE_SYSTEM_FILE) ||
	    (OCFS2_I(inode_out)->ip_flags & OCFS2_INODE_SYSTEM_FILE))
		goto out_unlock;

	ret = vfs_clone_file_prep_inodes(inode_in, pos_in, inode_out, pos_out,
			&len, is_dedupe);
	if (ret <= 0)
		goto out_unlock;

	/* Lock out changes to the allocation maps and remap. */
	down_write(&OCFS2_I(inode_in)->ip_alloc_sem);
	if (!same_inode)
		down_write_nested(&OCFS2_I(inode_out)->ip_alloc_sem,
				  SINGLE_DEPTH_NESTING);

	ret = ocfs2_reflink_remap_blocks(inode_in, in_bh, pos_in, inode_out,
					 out_bh, pos_out, len);

	/* Zap any page cache for the destination file's range. */
	if (!ret)
		truncate_inode_pages_range(&inode_out->i_data, pos_out,
					   PAGE_ALIGN(pos_out + len) - 1);

	up_write(&OCFS2_I(inode_in)->ip_alloc_sem);
	if (!same_inode)
		up_write(&OCFS2_I(inode_out)->ip_alloc_sem);
	if (ret) {
		mlog_errno(ret);
		goto out_unlock;
	}

	/*
	 * Empty the extent map so that we may get the right extent
	 * record from the disk.
	 */
	ocfs2_extent_map_trunc(inode_in, 0);
	ocfs2_extent_map_trunc(inode_out, 0);

	ret = ocfs2_reflink_update_dest(inode_out, out_bh, pos_out + len);
	if (ret) {
		mlog_errno(ret);
		goto out_unlock;
	}

	ocfs2_reflink_inodes_unlock(inode_in, in_bh, inode_out, out_bh);
	return 0;

out_unlock:
	ocfs2_reflink_inodes_unlock(inode_in, in_bh, inode_out, out_bh);
	return ret;
}