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
typedef  int umode_t ;
struct ubifs_inode {int ui_size; int /*<<< orphan*/  ui_mutex; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_budget_req {int new_ino; int new_dent; } ;
struct inode {int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct fscrypt_name {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int CALC_DENT_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dbg_gen (char*,struct dentry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  fname_len (struct fscrypt_name*) ; 
 int /*<<< orphan*/  fscrypt_free_filename (struct fscrypt_name*) ; 
 int fscrypt_setup_filename (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fscrypt_name*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int) ; 
 int ubifs_init_security (struct inode*,struct inode*,int /*<<< orphan*/ *) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_update (struct ubifs_info*,struct inode*,struct fscrypt_name*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* ubifs_new_inode (struct ubifs_info*,struct inode*,int) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 

__attribute__((used)) static int ubifs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct inode *inode;
	struct ubifs_inode *dir_ui = ubifs_inode(dir);
	struct ubifs_info *c = dir->i_sb->s_fs_info;
	int err, sz_change;
	struct ubifs_budget_req req = { .new_ino = 1, .new_dent = 1 };
	struct fscrypt_name nm;

	/*
	 * Budget request settings: new inode, new direntry and changing parent
	 * directory inode.
	 */

	dbg_gen("dent '%pd', mode %#hx in dir ino %lu",
		dentry, mode, dir->i_ino);

	err = ubifs_budget_space(c, &req);
	if (err)
		return err;

	err = fscrypt_setup_filename(dir, &dentry->d_name, 0, &nm);
	if (err)
		goto out_budg;

	sz_change = CALC_DENT_SIZE(fname_len(&nm));

	inode = ubifs_new_inode(c, dir, S_IFDIR | mode);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_fname;
	}

	err = ubifs_init_security(dir, inode, &dentry->d_name);
	if (err)
		goto out_inode;

	mutex_lock(&dir_ui->ui_mutex);
	insert_inode_hash(inode);
	inc_nlink(inode);
	inc_nlink(dir);
	dir->i_size += sz_change;
	dir_ui->ui_size = dir->i_size;
	dir->i_mtime = dir->i_ctime = inode->i_ctime;
	err = ubifs_jnl_update(c, dir, &nm, inode, 0, 0);
	if (err) {
		ubifs_err(c, "cannot create directory, error %d", err);
		goto out_cancel;
	}
	mutex_unlock(&dir_ui->ui_mutex);

	ubifs_release_budget(c, &req);
	d_instantiate(dentry, inode);
	fscrypt_free_filename(&nm);
	return 0;

out_cancel:
	dir->i_size -= sz_change;
	dir_ui->ui_size = dir->i_size;
	drop_nlink(dir);
	mutex_unlock(&dir_ui->ui_mutex);
out_inode:
	make_bad_inode(inode);
	iput(inode);
out_fname:
	fscrypt_free_filename(&nm);
out_budg:
	ubifs_release_budget(c, &req);
	return err;
}