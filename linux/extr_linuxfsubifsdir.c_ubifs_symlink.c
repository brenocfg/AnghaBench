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
struct ubifs_inode {int data_len; int ui_size; int /*<<< orphan*/  ui_mutex; scalar_t__ data; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_budget_req {int new_ino; int new_dent; int dirtied_ino; int /*<<< orphan*/  new_ino_d; } ;
struct inode {int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; scalar_t__ i_link; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct fscrypt_str {int len; scalar_t__ name; } ;
struct fscrypt_name {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int CALC_DENT_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  UBIFS_MAX_INO_DATA ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dbg_gen (char*,struct dentry*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fname_len (struct fscrypt_name*) ; 
 int fscrypt_encrypt_symlink (struct inode*,char const*,int,struct fscrypt_str*) ; 
 int /*<<< orphan*/  fscrypt_free_filename (struct fscrypt_name*) ; 
 int fscrypt_prepare_symlink (struct inode*,char const*,int,int /*<<< orphan*/ ,struct fscrypt_str*) ; 
 int fscrypt_setup_filename (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fscrypt_name*) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int ubifs_init_security (struct inode*,struct inode*,int /*<<< orphan*/ *) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_update (struct ubifs_info*,struct inode*,struct fscrypt_name*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* ubifs_new_inode (struct ubifs_info*,struct inode*,int) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 

__attribute__((used)) static int ubifs_symlink(struct inode *dir, struct dentry *dentry,
			 const char *symname)
{
	struct inode *inode;
	struct ubifs_inode *ui;
	struct ubifs_inode *dir_ui = ubifs_inode(dir);
	struct ubifs_info *c = dir->i_sb->s_fs_info;
	int err, sz_change, len = strlen(symname);
	struct fscrypt_str disk_link;
	struct ubifs_budget_req req = { .new_ino = 1, .new_dent = 1,
					.new_ino_d = ALIGN(len, 8),
					.dirtied_ino = 1 };
	struct fscrypt_name nm;

	dbg_gen("dent '%pd', target '%s' in dir ino %lu", dentry,
		symname, dir->i_ino);

	err = fscrypt_prepare_symlink(dir, symname, len, UBIFS_MAX_INO_DATA,
				      &disk_link);
	if (err)
		return err;

	/*
	 * Budget request settings: new inode, new direntry and changing parent
	 * directory inode.
	 */
	err = ubifs_budget_space(c, &req);
	if (err)
		return err;

	err = fscrypt_setup_filename(dir, &dentry->d_name, 0, &nm);
	if (err)
		goto out_budg;

	sz_change = CALC_DENT_SIZE(fname_len(&nm));

	inode = ubifs_new_inode(c, dir, S_IFLNK | S_IRWXUGO);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_fname;
	}

	ui = ubifs_inode(inode);
	ui->data = kmalloc(disk_link.len, GFP_NOFS);
	if (!ui->data) {
		err = -ENOMEM;
		goto out_inode;
	}

	if (IS_ENCRYPTED(inode)) {
		disk_link.name = ui->data; /* encrypt directly into ui->data */
		err = fscrypt_encrypt_symlink(inode, symname, len, &disk_link);
		if (err)
			goto out_inode;
	} else {
		memcpy(ui->data, disk_link.name, disk_link.len);
		inode->i_link = ui->data;
	}

	/*
	 * The terminating zero byte is not written to the flash media and it
	 * is put just to make later in-memory string processing simpler. Thus,
	 * data length is @disk_link.len - 1, not @disk_link.len.
	 */
	ui->data_len = disk_link.len - 1;
	inode->i_size = ubifs_inode(inode)->ui_size = disk_link.len - 1;

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

	insert_inode_hash(inode);
	d_instantiate(dentry, inode);
	err = 0;
	goto out_fname;

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