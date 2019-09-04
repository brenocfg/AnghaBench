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
struct ubifs_inode {int ui_size; int /*<<< orphan*/  data_len; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_budget_req {int new_dent; int dirtied_ino; int /*<<< orphan*/  dirtied_ino_d; } ;
struct inode {scalar_t__ i_nlink; int i_size; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; TYPE_1__* i_sb; } ;
struct fscrypt_name {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__ d_name; } ;
struct TYPE_3__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int CALC_DENT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int dbg_check_synced_i_size (struct ubifs_info*,struct inode*) ; 
 int /*<<< orphan*/  dbg_gen (char*,struct dentry*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  fscrypt_free_filename (struct fscrypt_name*) ; 
 int fscrypt_prepare_link (struct dentry*,struct inode*,struct dentry*) ; 
 int fscrypt_setup_filename (struct inode*,TYPE_2__*,int /*<<< orphan*/ ,struct fscrypt_name*) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  inode_is_locked (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  lock_2_inodes (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ubifs_add_orphan (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_delete_orphan (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_update (struct ubifs_info*,struct inode*,struct fscrypt_name*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  unlock_2_inodes (struct inode*,struct inode*) ; 

__attribute__((used)) static int ubifs_link(struct dentry *old_dentry, struct inode *dir,
		      struct dentry *dentry)
{
	struct ubifs_info *c = dir->i_sb->s_fs_info;
	struct inode *inode = d_inode(old_dentry);
	struct ubifs_inode *ui = ubifs_inode(inode);
	struct ubifs_inode *dir_ui = ubifs_inode(dir);
	int err, sz_change = CALC_DENT_SIZE(dentry->d_name.len);
	struct ubifs_budget_req req = { .new_dent = 1, .dirtied_ino = 2,
				.dirtied_ino_d = ALIGN(ui->data_len, 8) };
	struct fscrypt_name nm;

	/*
	 * Budget request settings: new direntry, changing the target inode,
	 * changing the parent inode.
	 */

	dbg_gen("dent '%pd' to ino %lu (nlink %d) in dir ino %lu",
		dentry, inode->i_ino,
		inode->i_nlink, dir->i_ino);
	ubifs_assert(c, inode_is_locked(dir));
	ubifs_assert(c, inode_is_locked(inode));

	err = fscrypt_prepare_link(old_dentry, dir, dentry);
	if (err)
		return err;

	err = fscrypt_setup_filename(dir, &dentry->d_name, 0, &nm);
	if (err)
		return err;

	err = dbg_check_synced_i_size(c, inode);
	if (err)
		goto out_fname;

	err = ubifs_budget_space(c, &req);
	if (err)
		goto out_fname;

	lock_2_inodes(dir, inode);

	/* Handle O_TMPFILE corner case, it is allowed to link a O_TMPFILE. */
	if (inode->i_nlink == 0)
		ubifs_delete_orphan(c, inode->i_ino);

	inc_nlink(inode);
	ihold(inode);
	inode->i_ctime = current_time(inode);
	dir->i_size += sz_change;
	dir_ui->ui_size = dir->i_size;
	dir->i_mtime = dir->i_ctime = inode->i_ctime;
	err = ubifs_jnl_update(c, dir, &nm, inode, 0, 0);
	if (err)
		goto out_cancel;
	unlock_2_inodes(dir, inode);

	ubifs_release_budget(c, &req);
	d_instantiate(dentry, inode);
	fscrypt_free_filename(&nm);
	return 0;

out_cancel:
	dir->i_size -= sz_change;
	dir_ui->ui_size = dir->i_size;
	drop_nlink(inode);
	if (inode->i_nlink == 0)
		ubifs_add_orphan(c, inode->i_ino);
	unlock_2_inodes(dir, inode);
	ubifs_release_budget(c, &req);
	iput(inode);
out_fname:
	fscrypt_free_filename(&nm);
	return err;
}