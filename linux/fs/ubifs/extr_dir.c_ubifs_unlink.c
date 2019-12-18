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
struct ubifs_inode {int ui_size; } ;
struct TYPE_4__ {scalar_t__ nospace_rp; scalar_t__ nospace; } ;
struct ubifs_info {TYPE_2__ bi; } ;
struct ubifs_budget_req {int mod_dent; int dirtied_ino; } ;
struct inode {unsigned int i_nlink; int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct fscrypt_name {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct TYPE_3__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int CALC_DENT_SIZE (int /*<<< orphan*/ ) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int dbg_check_synced_i_size (struct ubifs_info*,struct inode*) ; 
 int /*<<< orphan*/  dbg_gen (char*,struct dentry*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  fname_len (struct fscrypt_name*) ; 
 int /*<<< orphan*/  fscrypt_free_filename (struct fscrypt_name*) ; 
 int fscrypt_setup_filename (struct inode*,int /*<<< orphan*/ *,int,struct fscrypt_name*) ; 
 int /*<<< orphan*/  inode_is_locked (struct inode*) ; 
 int /*<<< orphan*/  lock_2_inodes (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_update (struct ubifs_info*,struct inode*,struct fscrypt_name*,struct inode*,int,int /*<<< orphan*/ ) ; 
 int ubifs_purge_xattrs (struct inode*) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  unlock_2_inodes (struct inode*,struct inode*) ; 

__attribute__((used)) static int ubifs_unlink(struct inode *dir, struct dentry *dentry)
{
	struct ubifs_info *c = dir->i_sb->s_fs_info;
	struct inode *inode = d_inode(dentry);
	struct ubifs_inode *dir_ui = ubifs_inode(dir);
	int err, sz_change, budgeted = 1;
	struct ubifs_budget_req req = { .mod_dent = 1, .dirtied_ino = 2 };
	unsigned int saved_nlink = inode->i_nlink;
	struct fscrypt_name nm;

	/*
	 * Budget request settings: deletion direntry, deletion inode (+1 for
	 * @dirtied_ino), changing the parent directory inode. If budgeting
	 * fails, go ahead anyway because we have extra space reserved for
	 * deletions.
	 */

	dbg_gen("dent '%pd' from ino %lu (nlink %d) in dir ino %lu",
		dentry, inode->i_ino,
		inode->i_nlink, dir->i_ino);

	err = fscrypt_setup_filename(dir, &dentry->d_name, 1, &nm);
	if (err)
		return err;

	err = ubifs_purge_xattrs(inode);
	if (err)
		return err;

	sz_change = CALC_DENT_SIZE(fname_len(&nm));

	ubifs_assert(c, inode_is_locked(dir));
	ubifs_assert(c, inode_is_locked(inode));
	err = dbg_check_synced_i_size(c, inode);
	if (err)
		goto out_fname;

	err = ubifs_budget_space(c, &req);
	if (err) {
		if (err != -ENOSPC)
			goto out_fname;
		budgeted = 0;
	}

	lock_2_inodes(dir, inode);
	inode->i_ctime = current_time(dir);
	drop_nlink(inode);
	dir->i_size -= sz_change;
	dir_ui->ui_size = dir->i_size;
	dir->i_mtime = dir->i_ctime = inode->i_ctime;
	err = ubifs_jnl_update(c, dir, &nm, inode, 1, 0);
	if (err)
		goto out_cancel;
	unlock_2_inodes(dir, inode);

	if (budgeted)
		ubifs_release_budget(c, &req);
	else {
		/* We've deleted something - clean the "no space" flags */
		c->bi.nospace = c->bi.nospace_rp = 0;
		smp_wmb();
	}
	fscrypt_free_filename(&nm);
	return 0;

out_cancel:
	dir->i_size += sz_change;
	dir_ui->ui_size = dir->i_size;
	set_nlink(inode, saved_nlink);
	unlock_2_inodes(dir, inode);
	if (budgeted)
		ubifs_release_budget(c, &req);
out_fname:
	fscrypt_free_filename(&nm);
	return err;
}