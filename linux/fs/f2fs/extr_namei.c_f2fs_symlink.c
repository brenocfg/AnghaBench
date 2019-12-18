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
struct inode {TYPE_2__* i_mapping; int /*<<< orphan*/  i_ino; int /*<<< orphan*/ * i_op; TYPE_1__* i_sb; } ;
struct fscrypt_str {unsigned char* name; int len; } ;
struct f2fs_sb_info {int /*<<< orphan*/  sb; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * a_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSPC ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  d_instantiate_new (struct dentry*,struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int f2fs_add_link (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  f2fs_alloc_nid_done (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_cp_error (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_dblock_aops ; 
 int /*<<< orphan*/  f2fs_encrypted_symlink_inode_operations ; 
 int /*<<< orphan*/  f2fs_handle_failed_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_is_checkpoint_ready (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_lock_op (struct f2fs_sb_info*) ; 
 struct inode* f2fs_new_inode (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_symlink_inode_operations ; 
 int /*<<< orphan*/  f2fs_sync_fs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_unlink (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  filemap_write_and_wait_range (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int fscrypt_encrypt_symlink (struct inode*,char const*,size_t,struct fscrypt_str*) ; 
 int fscrypt_prepare_symlink (struct inode*,char const*,size_t,int /*<<< orphan*/ ,struct fscrypt_str*) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  kvfree (unsigned char*) ; 
 int page_symlink (struct inode*,unsigned char*,int) ; 
 size_t strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_symlink(struct inode *dir, struct dentry *dentry,
					const char *symname)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dir);
	struct inode *inode;
	size_t len = strlen(symname);
	struct fscrypt_str disk_link;
	int err;

	if (unlikely(f2fs_cp_error(sbi)))
		return -EIO;
	if (!f2fs_is_checkpoint_ready(sbi))
		return -ENOSPC;

	err = fscrypt_prepare_symlink(dir, symname, len, dir->i_sb->s_blocksize,
				      &disk_link);
	if (err)
		return err;

	err = dquot_initialize(dir);
	if (err)
		return err;

	inode = f2fs_new_inode(dir, S_IFLNK | S_IRWXUGO);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	if (IS_ENCRYPTED(inode))
		inode->i_op = &f2fs_encrypted_symlink_inode_operations;
	else
		inode->i_op = &f2fs_symlink_inode_operations;
	inode_nohighmem(inode);
	inode->i_mapping->a_ops = &f2fs_dblock_aops;

	f2fs_lock_op(sbi);
	err = f2fs_add_link(dentry, inode);
	if (err)
		goto out_f2fs_handle_failed_inode;
	f2fs_unlock_op(sbi);
	f2fs_alloc_nid_done(sbi, inode->i_ino);

	err = fscrypt_encrypt_symlink(inode, symname, len, &disk_link);
	if (err)
		goto err_out;

	err = page_symlink(inode, disk_link.name, disk_link.len);

err_out:
	d_instantiate_new(dentry, inode);

	/*
	 * Let's flush symlink data in order to avoid broken symlink as much as
	 * possible. Nevertheless, fsyncing is the best way, but there is no
	 * way to get a file descriptor in order to flush that.
	 *
	 * Note that, it needs to do dir->fsync to make this recoverable.
	 * If the symlink path is stored into inline_data, there is no
	 * performance regression.
	 */
	if (!err) {
		filemap_write_and_wait_range(inode->i_mapping, 0,
							disk_link.len - 1);

		if (IS_DIRSYNC(dir))
			f2fs_sync_fs(sbi->sb, 1);
	} else {
		f2fs_unlink(dir, dentry);
	}

	f2fs_balance_fs(sbi, true);
	goto out_free_encrypted_link;

out_f2fs_handle_failed_inode:
	f2fs_handle_failed_inode(inode);
out_free_encrypted_link:
	if (disk_link.name != (unsigned char *)symname)
		kvfree(disk_link.name);
	return err;
}