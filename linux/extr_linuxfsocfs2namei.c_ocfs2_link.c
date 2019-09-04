#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ocfs2_super {int /*<<< orphan*/  sb; int /*<<< orphan*/  uuid_str; } ;
struct ocfs2_dir_lookup_result {int /*<<< orphan*/ * member_0; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_ctime_nsec; int /*<<< orphan*/  i_ctime; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {TYPE_2__ i_ctime; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; struct dentry* d_parent; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_6__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int EIO ; 
 int EMLINK ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 TYPE_2__ current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_add_entry (int /*<<< orphan*/ *,struct dentry*,struct inode*,scalar_t__,struct buffer_head*,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  ocfs2_add_links_count (struct ocfs2_dinode*,int) ; 
 int /*<<< orphan*/  ocfs2_block_signals (int /*<<< orphan*/ *) ; 
 int ocfs2_check_dir_for_entry (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_dentry_attach_lock (struct dentry*,struct inode*,scalar_t__) ; 
 int ocfs2_double_lock (struct ocfs2_super*,struct buffer_head**,struct inode*,struct buffer_head**,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_double_unlock (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ocfs2_free_dir_lookup_result (struct ocfs2_dir_lookup_result*) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_link_credits (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_link_max (struct ocfs2_super*) ; 
 int ocfs2_lookup_ino_from_name (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int ocfs2_prepare_dir_for_insert (struct ocfs2_super*,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_dir_lookup_result*) ; 
 scalar_t__ ocfs2_read_links_count (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_set_links_count (struct ocfs2_dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_unblock_signals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_link (unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_link(struct dentry *old_dentry,
		      struct inode *dir,
		      struct dentry *dentry)
{
	handle_t *handle;
	struct inode *inode = d_inode(old_dentry);
	struct inode *old_dir = d_inode(old_dentry->d_parent);
	int err;
	struct buffer_head *fe_bh = NULL;
	struct buffer_head *old_dir_bh = NULL;
	struct buffer_head *parent_fe_bh = NULL;
	struct ocfs2_dinode *fe = NULL;
	struct ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	struct ocfs2_dir_lookup_result lookup = { NULL, };
	sigset_t oldset;
	u64 old_de_ino;

	trace_ocfs2_link((unsigned long long)OCFS2_I(inode)->ip_blkno,
			 old_dentry->d_name.len, old_dentry->d_name.name,
			 dentry->d_name.len, dentry->d_name.name);

	if (S_ISDIR(inode->i_mode))
		return -EPERM;

	err = dquot_initialize(dir);
	if (err) {
		mlog_errno(err);
		return err;
	}

	err = ocfs2_double_lock(osb, &old_dir_bh, old_dir,
			&parent_fe_bh, dir, 0);
	if (err < 0) {
		if (err != -ENOENT)
			mlog_errno(err);
		return err;
	}

	/* make sure both dirs have bhs
	 * get an extra ref on old_dir_bh if old==new */
	if (!parent_fe_bh) {
		if (old_dir_bh) {
			parent_fe_bh = old_dir_bh;
			get_bh(parent_fe_bh);
		} else {
			mlog(ML_ERROR, "%s: no old_dir_bh!\n", osb->uuid_str);
			err = -EIO;
			goto out;
		}
	}

	if (!dir->i_nlink) {
		err = -ENOENT;
		goto out;
	}

	err = ocfs2_lookup_ino_from_name(old_dir, old_dentry->d_name.name,
			old_dentry->d_name.len, &old_de_ino);
	if (err) {
		err = -ENOENT;
		goto out;
	}

	/*
	 * Check whether another node removed the source inode while we
	 * were in the vfs.
	 */
	if (old_de_ino != OCFS2_I(inode)->ip_blkno) {
		err = -ENOENT;
		goto out;
	}

	err = ocfs2_check_dir_for_entry(dir, dentry->d_name.name,
					dentry->d_name.len);
	if (err)
		goto out;

	err = ocfs2_prepare_dir_for_insert(osb, dir, parent_fe_bh,
					   dentry->d_name.name,
					   dentry->d_name.len, &lookup);
	if (err < 0) {
		mlog_errno(err);
		goto out;
	}

	err = ocfs2_inode_lock(inode, &fe_bh, 1);
	if (err < 0) {
		if (err != -ENOENT)
			mlog_errno(err);
		goto out;
	}

	fe = (struct ocfs2_dinode *) fe_bh->b_data;
	if (ocfs2_read_links_count(fe) >= ocfs2_link_max(osb)) {
		err = -EMLINK;
		goto out_unlock_inode;
	}

	handle = ocfs2_start_trans(osb, ocfs2_link_credits(osb->sb));
	if (IS_ERR(handle)) {
		err = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(err);
		goto out_unlock_inode;
	}

	/* Starting to change things, restart is no longer possible. */
	ocfs2_block_signals(&oldset);

	err = ocfs2_journal_access_di(handle, INODE_CACHE(inode), fe_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (err < 0) {
		mlog_errno(err);
		goto out_commit;
	}

	inc_nlink(inode);
	inode->i_ctime = current_time(inode);
	ocfs2_set_links_count(fe, inode->i_nlink);
	fe->i_ctime = cpu_to_le64(inode->i_ctime.tv_sec);
	fe->i_ctime_nsec = cpu_to_le32(inode->i_ctime.tv_nsec);
	ocfs2_journal_dirty(handle, fe_bh);

	err = ocfs2_add_entry(handle, dentry, inode,
			      OCFS2_I(inode)->ip_blkno,
			      parent_fe_bh, &lookup);
	if (err) {
		ocfs2_add_links_count(fe, -1);
		drop_nlink(inode);
		mlog_errno(err);
		goto out_commit;
	}

	err = ocfs2_dentry_attach_lock(dentry, inode, OCFS2_I(dir)->ip_blkno);
	if (err) {
		mlog_errno(err);
		goto out_commit;
	}

	ihold(inode);
	d_instantiate(dentry, inode);

out_commit:
	ocfs2_commit_trans(osb, handle);
	ocfs2_unblock_signals(&oldset);
out_unlock_inode:
	ocfs2_inode_unlock(inode, 1);

out:
	ocfs2_double_unlock(old_dir, dir);

	brelse(fe_bh);
	brelse(parent_fe_bh);
	brelse(old_dir_bh);

	ocfs2_free_dir_lookup_result(&lookup);

	if (err)
		mlog_errno(err);

	return err;
}