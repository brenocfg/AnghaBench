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
typedef  int /*<<< orphan*/  umode_t ;
struct ubifs_inode {int dirty; int /*<<< orphan*/  ui_mutex; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_budget_req {int new_ino; int new_dent; int dirtied_ino; } ;
struct inode {int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct fscrypt_name {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  WHITEOUT_DEV ; 
 int /*<<< orphan*/  d_tmpfile (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dbg_gen (char*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  fscrypt_free_filename (struct fscrypt_name*) ; 
 int fscrypt_setup_filename (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fscrypt_name*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int) ; 
 int /*<<< orphan*/  ubifs_file_inode_operations ; 
 int ubifs_init_security (struct inode*,struct inode*,int /*<<< orphan*/ *) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_update (struct ubifs_info*,struct inode*,struct fscrypt_name*,struct inode*,int,int /*<<< orphan*/ ) ; 
 struct inode* ubifs_new_inode (struct ubifs_info*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 

__attribute__((used)) static int do_tmpfile(struct inode *dir, struct dentry *dentry,
		      umode_t mode, struct inode **whiteout)
{
	struct inode *inode;
	struct ubifs_info *c = dir->i_sb->s_fs_info;
	struct ubifs_budget_req req = { .new_ino = 1, .new_dent = 1};
	struct ubifs_budget_req ino_req = { .dirtied_ino = 1 };
	struct ubifs_inode *ui, *dir_ui = ubifs_inode(dir);
	int err, instantiated = 0;
	struct fscrypt_name nm;

	/*
	 * Budget request settings: new dirty inode, new direntry,
	 * budget for dirtied inode will be released via writeback.
	 */

	dbg_gen("dent '%pd', mode %#hx in dir ino %lu",
		dentry, mode, dir->i_ino);

	err = fscrypt_setup_filename(dir, &dentry->d_name, 0, &nm);
	if (err)
		return err;

	err = ubifs_budget_space(c, &req);
	if (err) {
		fscrypt_free_filename(&nm);
		return err;
	}

	err = ubifs_budget_space(c, &ino_req);
	if (err) {
		ubifs_release_budget(c, &req);
		fscrypt_free_filename(&nm);
		return err;
	}

	inode = ubifs_new_inode(c, dir, mode);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_budg;
	}
	ui = ubifs_inode(inode);

	if (whiteout) {
		init_special_inode(inode, inode->i_mode, WHITEOUT_DEV);
		ubifs_assert(c, inode->i_op == &ubifs_file_inode_operations);
	}

	err = ubifs_init_security(dir, inode, &dentry->d_name);
	if (err)
		goto out_inode;

	mutex_lock(&ui->ui_mutex);
	insert_inode_hash(inode);

	if (whiteout) {
		mark_inode_dirty(inode);
		drop_nlink(inode);
		*whiteout = inode;
	} else {
		d_tmpfile(dentry, inode);
	}
	ubifs_assert(c, ui->dirty);

	instantiated = 1;
	mutex_unlock(&ui->ui_mutex);

	mutex_lock(&dir_ui->ui_mutex);
	err = ubifs_jnl_update(c, dir, &nm, inode, 1, 0);
	if (err)
		goto out_cancel;
	mutex_unlock(&dir_ui->ui_mutex);

	ubifs_release_budget(c, &req);

	return 0;

out_cancel:
	mutex_unlock(&dir_ui->ui_mutex);
out_inode:
	make_bad_inode(inode);
	if (!instantiated)
		iput(inode);
out_budg:
	ubifs_release_budget(c, &req);
	if (!instantiated)
		ubifs_release_budget(c, &ino_req);
	fscrypt_free_filename(&nm);
	ubifs_err(c, "cannot create temporary file, error %d", err);
	return err;
}