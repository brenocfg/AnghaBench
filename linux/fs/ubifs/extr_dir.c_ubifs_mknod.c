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
typedef  union ubifs_dev_desc {int dummy; } ubifs_dev_desc ;
typedef  int /*<<< orphan*/  umode_t ;
struct ubifs_inode {int ui_size; int data_len; int /*<<< orphan*/  ui_mutex; union ubifs_dev_desc* data; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_budget_req {int new_ino; int new_dent; int dirtied_ino; int /*<<< orphan*/  new_ino_d; } ;
struct inode {int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct fscrypt_name {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int CALC_DENT_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dbg_gen (char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fname_len (struct fscrypt_name*) ; 
 int /*<<< orphan*/  fscrypt_free_filename (struct fscrypt_name*) ; 
 int fscrypt_setup_filename (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fscrypt_name*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (union ubifs_dev_desc*) ; 
 union ubifs_dev_desc* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int ubifs_encode_dev (union ubifs_dev_desc*,int /*<<< orphan*/ ) ; 
 int ubifs_init_security (struct inode*,struct inode*,int /*<<< orphan*/ *) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_update (struct ubifs_info*,struct inode*,struct fscrypt_name*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* ubifs_new_inode (struct ubifs_info*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 

__attribute__((used)) static int ubifs_mknod(struct inode *dir, struct dentry *dentry,
		       umode_t mode, dev_t rdev)
{
	struct inode *inode;
	struct ubifs_inode *ui;
	struct ubifs_inode *dir_ui = ubifs_inode(dir);
	struct ubifs_info *c = dir->i_sb->s_fs_info;
	union ubifs_dev_desc *dev = NULL;
	int sz_change;
	int err, devlen = 0;
	struct ubifs_budget_req req = { .new_ino = 1, .new_dent = 1,
					.dirtied_ino = 1 };
	struct fscrypt_name nm;

	/*
	 * Budget request settings: new inode, new direntry and changing parent
	 * directory inode.
	 */

	dbg_gen("dent '%pd' in dir ino %lu", dentry, dir->i_ino);

	if (S_ISBLK(mode) || S_ISCHR(mode)) {
		dev = kmalloc(sizeof(union ubifs_dev_desc), GFP_NOFS);
		if (!dev)
			return -ENOMEM;
		devlen = ubifs_encode_dev(dev, rdev);
	}

	req.new_ino_d = ALIGN(devlen, 8);
	err = ubifs_budget_space(c, &req);
	if (err) {
		kfree(dev);
		return err;
	}

	err = fscrypt_setup_filename(dir, &dentry->d_name, 0, &nm);
	if (err) {
		kfree(dev);
		goto out_budg;
	}

	sz_change = CALC_DENT_SIZE(fname_len(&nm));

	inode = ubifs_new_inode(c, dir, mode);
	if (IS_ERR(inode)) {
		kfree(dev);
		err = PTR_ERR(inode);
		goto out_fname;
	}

	init_special_inode(inode, inode->i_mode, rdev);
	inode->i_size = ubifs_inode(inode)->ui_size = devlen;
	ui = ubifs_inode(inode);
	ui->data = dev;
	ui->data_len = devlen;

	err = ubifs_init_security(dir, inode, &dentry->d_name);
	if (err)
		goto out_inode;

	mutex_lock(&dir_ui->ui_mutex);
	dir->i_size += sz_change;
	dir_ui->ui_size = dir->i_size;
	dir->i_mtime = dir->i_ctime = inode->i_ctime;
	err = ubifs_jnl_update(c, dir, &nm, inode, 0, 0);
	if (err)
		goto out_cancel;
	mutex_unlock(&dir_ui->ui_mutex);

	ubifs_release_budget(c, &req);
	insert_inode_hash(inode);
	d_instantiate(dentry, inode);
	fscrypt_free_filename(&nm);
	return 0;

out_cancel:
	dir->i_size -= sz_change;
	dir_ui->ui_size = dir->i_size;
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