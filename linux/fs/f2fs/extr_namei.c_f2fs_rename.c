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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_state; void* i_ctime; int /*<<< orphan*/  i_nlink; } ;
struct f2fs_sb_info {int /*<<< orphan*/  sb; } ;
struct f2fs_dir_entry {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; struct inode* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_sem; int /*<<< orphan*/  i_pino; int /*<<< orphan*/  i_projid; } ;
struct TYPE_3__ {scalar_t__ fsync_mode; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int ENOSPC ; 
 int ENOTEMPTY ; 
 int EXDEV ; 
 TYPE_2__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 TYPE_1__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  FI_INC_LINK ; 
 int /*<<< orphan*/  FI_PROJ_INHERIT ; 
 scalar_t__ FSYNC_MODE_STRICT ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  I_LINKABLE ; 
 int PTR_ERR (struct page*) ; 
 unsigned int RENAME_WHITEOUT ; 
 int /*<<< orphan*/  REQ_TIME ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANS_DIR_INO ; 
 void* current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int dquot_initialize (struct inode*) ; 
 int f2fs_acquire_orphan_inode (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_add_ino_entry (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int f2fs_add_link (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  f2fs_add_orphan_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_cp_error (struct f2fs_sb_info*) ; 
 int f2fs_create_whiteout (struct inode*,struct inode**) ; 
 int /*<<< orphan*/  f2fs_delete_entry (struct f2fs_dir_entry*,struct page*,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_empty_dir (struct inode*) ; 
 struct f2fs_dir_entry* f2fs_find_entry (struct inode*,int /*<<< orphan*/ *,struct page**) ; 
 int f2fs_has_inline_dentry (struct inode*) ; 
 int /*<<< orphan*/  f2fs_i_links_write (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_is_checkpoint_ready (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_lock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 struct f2fs_dir_entry* f2fs_parent_dir (struct inode*,struct page**) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_release_orphan_inode (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_set_link (struct inode*,struct f2fs_dir_entry*,struct page*,struct inode*) ; 
 int /*<<< orphan*/  f2fs_sync_fs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_update_time (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_lost_pino (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  projid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int f2fs_rename(struct inode *old_dir, struct dentry *old_dentry,
			struct inode *new_dir, struct dentry *new_dentry,
			unsigned int flags)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(old_dir);
	struct inode *old_inode = d_inode(old_dentry);
	struct inode *new_inode = d_inode(new_dentry);
	struct inode *whiteout = NULL;
	struct page *old_dir_page;
	struct page *old_page, *new_page = NULL;
	struct f2fs_dir_entry *old_dir_entry = NULL;
	struct f2fs_dir_entry *old_entry;
	struct f2fs_dir_entry *new_entry;
	bool is_old_inline = f2fs_has_inline_dentry(old_dir);
	int err;

	if (unlikely(f2fs_cp_error(sbi)))
		return -EIO;
	if (!f2fs_is_checkpoint_ready(sbi))
		return -ENOSPC;

	if (is_inode_flag_set(new_dir, FI_PROJ_INHERIT) &&
			(!projid_eq(F2FS_I(new_dir)->i_projid,
			F2FS_I(old_dentry->d_inode)->i_projid)))
		return -EXDEV;

	err = dquot_initialize(old_dir);
	if (err)
		goto out;

	err = dquot_initialize(new_dir);
	if (err)
		goto out;

	if (new_inode) {
		err = dquot_initialize(new_inode);
		if (err)
			goto out;
	}

	err = -ENOENT;
	old_entry = f2fs_find_entry(old_dir, &old_dentry->d_name, &old_page);
	if (!old_entry) {
		if (IS_ERR(old_page))
			err = PTR_ERR(old_page);
		goto out;
	}

	if (S_ISDIR(old_inode->i_mode)) {
		old_dir_entry = f2fs_parent_dir(old_inode, &old_dir_page);
		if (!old_dir_entry) {
			if (IS_ERR(old_dir_page))
				err = PTR_ERR(old_dir_page);
			goto out_old;
		}
	}

	if (flags & RENAME_WHITEOUT) {
		err = f2fs_create_whiteout(old_dir, &whiteout);
		if (err)
			goto out_dir;
	}

	if (new_inode) {

		err = -ENOTEMPTY;
		if (old_dir_entry && !f2fs_empty_dir(new_inode))
			goto out_whiteout;

		err = -ENOENT;
		new_entry = f2fs_find_entry(new_dir, &new_dentry->d_name,
						&new_page);
		if (!new_entry) {
			if (IS_ERR(new_page))
				err = PTR_ERR(new_page);
			goto out_whiteout;
		}

		f2fs_balance_fs(sbi, true);

		f2fs_lock_op(sbi);

		err = f2fs_acquire_orphan_inode(sbi);
		if (err)
			goto put_out_dir;

		f2fs_set_link(new_dir, new_entry, new_page, old_inode);

		new_inode->i_ctime = current_time(new_inode);
		down_write(&F2FS_I(new_inode)->i_sem);
		if (old_dir_entry)
			f2fs_i_links_write(new_inode, false);
		f2fs_i_links_write(new_inode, false);
		up_write(&F2FS_I(new_inode)->i_sem);

		if (!new_inode->i_nlink)
			f2fs_add_orphan_inode(new_inode);
		else
			f2fs_release_orphan_inode(sbi);
	} else {
		f2fs_balance_fs(sbi, true);

		f2fs_lock_op(sbi);

		err = f2fs_add_link(new_dentry, old_inode);
		if (err) {
			f2fs_unlock_op(sbi);
			goto out_whiteout;
		}

		if (old_dir_entry)
			f2fs_i_links_write(new_dir, true);

		/*
		 * old entry and new entry can locate in the same inline
		 * dentry in inode, when attaching new entry in inline dentry,
		 * it could force inline dentry conversion, after that,
		 * old_entry and old_page will point to wrong address, in
		 * order to avoid this, let's do the check and update here.
		 */
		if (is_old_inline && !f2fs_has_inline_dentry(old_dir)) {
			f2fs_put_page(old_page, 0);
			old_page = NULL;

			old_entry = f2fs_find_entry(old_dir,
						&old_dentry->d_name, &old_page);
			if (!old_entry) {
				err = -ENOENT;
				if (IS_ERR(old_page))
					err = PTR_ERR(old_page);
				f2fs_unlock_op(sbi);
				goto out_whiteout;
			}
		}
	}

	down_write(&F2FS_I(old_inode)->i_sem);
	if (!old_dir_entry || whiteout)
		file_lost_pino(old_inode);
	else
		F2FS_I(old_inode)->i_pino = new_dir->i_ino;
	up_write(&F2FS_I(old_inode)->i_sem);

	old_inode->i_ctime = current_time(old_inode);
	f2fs_mark_inode_dirty_sync(old_inode, false);

	f2fs_delete_entry(old_entry, old_page, old_dir, NULL);

	if (whiteout) {
		whiteout->i_state |= I_LINKABLE;
		set_inode_flag(whiteout, FI_INC_LINK);
		err = f2fs_add_link(old_dentry, whiteout);
		if (err)
			goto put_out_dir;
		whiteout->i_state &= ~I_LINKABLE;
		iput(whiteout);
	}

	if (old_dir_entry) {
		if (old_dir != new_dir && !whiteout)
			f2fs_set_link(old_inode, old_dir_entry,
						old_dir_page, new_dir);
		else
			f2fs_put_page(old_dir_page, 0);
		f2fs_i_links_write(old_dir, false);
	}
	if (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_STRICT) {
		f2fs_add_ino_entry(sbi, new_dir->i_ino, TRANS_DIR_INO);
		if (S_ISDIR(old_inode->i_mode))
			f2fs_add_ino_entry(sbi, old_inode->i_ino,
							TRANS_DIR_INO);
	}

	f2fs_unlock_op(sbi);

	if (IS_DIRSYNC(old_dir) || IS_DIRSYNC(new_dir))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_update_time(sbi, REQ_TIME);
	return 0;

put_out_dir:
	f2fs_unlock_op(sbi);
	if (new_page)
		f2fs_put_page(new_page, 0);
out_whiteout:
	if (whiteout)
		iput(whiteout);
out_dir:
	if (old_dir_entry)
		f2fs_put_page(old_dir_page, 0);
out_old:
	f2fs_put_page(old_page, 0);
out:
	return err;
}