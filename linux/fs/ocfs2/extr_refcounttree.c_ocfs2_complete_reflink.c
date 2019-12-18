#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_dinode {int /*<<< orphan*/  i_mtime_nsec; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime_nsec; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_attr; int /*<<< orphan*/  i_dyn_features; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_clusters; int /*<<< orphan*/  i_xattr_inline_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mtime; TYPE_1__ i_ctime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_blocks; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_dyn_features; int /*<<< orphan*/  ip_attr; int /*<<< orphan*/  ip_clusters; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INODE_UPDATE_CREDITS ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 TYPE_1__ current_time (struct inode*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_complete_reflink(struct inode *s_inode,
				  struct buffer_head *s_bh,
				  struct inode *t_inode,
				  struct buffer_head *t_bh,
				  bool preserve)
{
	int ret;
	handle_t *handle;
	struct ocfs2_dinode *s_di = (struct ocfs2_dinode *)s_bh->b_data;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)t_bh->b_data;
	loff_t size = i_size_read(s_inode);

	handle = ocfs2_start_trans(OCFS2_SB(t_inode->i_sb),
				   OCFS2_INODE_UPDATE_CREDITS);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		return ret;
	}

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(t_inode), t_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	spin_lock(&OCFS2_I(t_inode)->ip_lock);
	OCFS2_I(t_inode)->ip_clusters = OCFS2_I(s_inode)->ip_clusters;
	OCFS2_I(t_inode)->ip_attr = OCFS2_I(s_inode)->ip_attr;
	OCFS2_I(t_inode)->ip_dyn_features = OCFS2_I(s_inode)->ip_dyn_features;
	spin_unlock(&OCFS2_I(t_inode)->ip_lock);
	i_size_write(t_inode, size);
	t_inode->i_blocks = s_inode->i_blocks;

	di->i_xattr_inline_size = s_di->i_xattr_inline_size;
	di->i_clusters = s_di->i_clusters;
	di->i_size = s_di->i_size;
	di->i_dyn_features = s_di->i_dyn_features;
	di->i_attr = s_di->i_attr;

	if (preserve) {
		t_inode->i_uid = s_inode->i_uid;
		t_inode->i_gid = s_inode->i_gid;
		t_inode->i_mode = s_inode->i_mode;
		di->i_uid = s_di->i_uid;
		di->i_gid = s_di->i_gid;
		di->i_mode = s_di->i_mode;

		/*
		 * update time.
		 * we want mtime to appear identical to the source and
		 * update ctime.
		 */
		t_inode->i_ctime = current_time(t_inode);

		di->i_ctime = cpu_to_le64(t_inode->i_ctime.tv_sec);
		di->i_ctime_nsec = cpu_to_le32(t_inode->i_ctime.tv_nsec);

		t_inode->i_mtime = s_inode->i_mtime;
		di->i_mtime = s_di->i_mtime;
		di->i_mtime_nsec = s_di->i_mtime_nsec;
	}

	ocfs2_journal_dirty(handle, t_bh);

out_commit:
	ocfs2_commit_trans(OCFS2_SB(t_inode->i_sb), handle);
	return ret;
}