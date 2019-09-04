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
typedef  scalar_t__ u64 ;
struct ocfs2_inode_info {int ip_dyn_features; int /*<<< orphan*/  ip_alloc_sem; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_convert_inline_data_to_extents (struct inode*,struct buffer_head*) ; 
 int ocfs2_extend_no_holes (struct inode*,struct buffer_head*,scalar_t__,scalar_t__) ; 
 int ocfs2_simple_size_update (struct inode*,struct buffer_head*,scalar_t__) ; 
 scalar_t__ ocfs2_size_fits_inline_data (struct buffer_head*,scalar_t__) ; 
 scalar_t__ ocfs2_sparse_alloc (int /*<<< orphan*/ ) ; 
 int ocfs2_zero_extend (struct inode*,struct buffer_head*,scalar_t__) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_extend_file(struct inode *inode,
			     struct buffer_head *di_bh,
			     u64 new_i_size)
{
	int ret = 0;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);

	BUG_ON(!di_bh);

	/* setattr sometimes calls us like this. */
	if (new_i_size == 0)
		goto out;

	if (i_size_read(inode) == new_i_size)
		goto out;
	BUG_ON(new_i_size < i_size_read(inode));

	/*
	 * The alloc sem blocks people in read/write from reading our
	 * allocation until we're done changing it. We depend on
	 * i_mutex to block other extend/truncate calls while we're
	 * here.  We even have to hold it for sparse files because there
	 * might be some tail zeroing.
	 */
	down_write(&oi->ip_alloc_sem);

	if (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		/*
		 * We can optimize small extends by keeping the inodes
		 * inline data.
		 */
		if (ocfs2_size_fits_inline_data(di_bh, new_i_size)) {
			up_write(&oi->ip_alloc_sem);
			goto out_update_size;
		}

		ret = ocfs2_convert_inline_data_to_extents(inode, di_bh);
		if (ret) {
			up_write(&oi->ip_alloc_sem);
			mlog_errno(ret);
			goto out;
		}
	}

	if (ocfs2_sparse_alloc(OCFS2_SB(inode->i_sb)))
		ret = ocfs2_zero_extend(inode, di_bh, new_i_size);
	else
		ret = ocfs2_extend_no_holes(inode, di_bh, new_i_size,
					    new_i_size);

	up_write(&oi->ip_alloc_sem);

	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

out_update_size:
	ret = ocfs2_simple_size_update(inode, di_bh, new_i_size);
	if (ret < 0)
		mlog_errno(ret);

out:
	return ret;
}