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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_blocks; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  ip_lock; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INODE_UPDATE_CREDITS ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_inode_sector_count (struct inode*) ; 
 int ocfs2_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ocfs2_reflink_update_dest(struct inode *dest,
			      struct buffer_head *d_bh,
			      loff_t newlen)
{
	handle_t *handle;
	int ret;

	dest->i_blocks = ocfs2_inode_sector_count(dest);

	if (newlen <= i_size_read(dest))
		return 0;

	handle = ocfs2_start_trans(OCFS2_SB(dest->i_sb),
				   OCFS2_INODE_UPDATE_CREDITS);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		return ret;
	}

	/* Extend i_size if needed. */
	spin_lock(&OCFS2_I(dest)->ip_lock);
	if (newlen > i_size_read(dest))
		i_size_write(dest, newlen);
	spin_unlock(&OCFS2_I(dest)->ip_lock);
	dest->i_ctime = dest->i_mtime = current_time(dest);

	ret = ocfs2_mark_inode_dirty(handle, dest, d_bh);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

out_commit:
	ocfs2_commit_trans(OCFS2_SB(dest->i_sb), handle);
	return ret;
}