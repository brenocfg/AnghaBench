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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {char* i_link; int i_size; int /*<<< orphan*/ * i_op; TYPE_1__* i_sb; } ;
struct fscrypt_str {int len; unsigned char* name; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
typedef  struct inode handle_t ;
struct TYPE_6__ {int i_disksize; int /*<<< orphan*/  i_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int EIO ; 
 int EXT4_DATA_TRANS_BLOCKS (TYPE_1__*) ; 
 int /*<<< orphan*/  EXT4_HT_DIR ; 
 TYPE_3__* EXT4_I (struct inode*) ; 
 int EXT4_INDEX_EXTRA_TRANS_BLOCKS ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int EXT4_MAXQUOTAS_INIT_BLOCKS (TYPE_1__*) ; 
 int EXT4_N_BLOCKS ; 
 int /*<<< orphan*/  EXT4_SB (TYPE_1__*) ; 
 int EXT4_XATTR_TRANS_BLOCKS ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int __page_symlink (struct inode*,unsigned char*,int,int) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int ext4_add_nondir (struct inode*,struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ext4_clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_encrypted_symlink_inode_operations ; 
 int /*<<< orphan*/  ext4_fast_symlink_inode_operations ; 
 int /*<<< orphan*/  ext4_forced_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_handle_sync (struct inode*) ; 
 struct inode* ext4_journal_current_handle () ; 
 struct inode* ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (struct inode*) ; 
 struct inode* ext4_new_inode_start_handle (struct inode*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ext4_orphan_add (struct inode*,struct inode*) ; 
 int ext4_orphan_del (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ext4_set_aops (struct inode*) ; 
 int /*<<< orphan*/  ext4_symlink_inode_operations ; 
 int fscrypt_encrypt_symlink (struct inode*,char const*,int,struct fscrypt_str*) ; 
 int fscrypt_prepare_symlink (struct inode*,char const*,int,int /*<<< orphan*/ ,struct fscrypt_str*) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,int) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 int strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int ext4_symlink(struct inode *dir,
			struct dentry *dentry, const char *symname)
{
	handle_t *handle;
	struct inode *inode;
	int err, len = strlen(symname);
	int credits;
	struct fscrypt_str disk_link;

	if (unlikely(ext4_forced_shutdown(EXT4_SB(dir->i_sb))))
		return -EIO;

	err = fscrypt_prepare_symlink(dir, symname, len, dir->i_sb->s_blocksize,
				      &disk_link);
	if (err)
		return err;

	err = dquot_initialize(dir);
	if (err)
		return err;

	if ((disk_link.len > EXT4_N_BLOCKS * 4)) {
		/*
		 * For non-fast symlinks, we just allocate inode and put it on
		 * orphan list in the first transaction => we need bitmap,
		 * group descriptor, sb, inode block, quota blocks, and
		 * possibly selinux xattr blocks.
		 */
		credits = 4 + EXT4_MAXQUOTAS_INIT_BLOCKS(dir->i_sb) +
			  EXT4_XATTR_TRANS_BLOCKS;
	} else {
		/*
		 * Fast symlink. We have to add entry to directory
		 * (EXT4_DATA_TRANS_BLOCKS + EXT4_INDEX_EXTRA_TRANS_BLOCKS),
		 * allocate new inode (bitmap, group descriptor, inode block,
		 * quota blocks, sb is already counted in previous macros).
		 */
		credits = EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
			  EXT4_INDEX_EXTRA_TRANS_BLOCKS + 3;
	}

	inode = ext4_new_inode_start_handle(dir, S_IFLNK|S_IRWXUGO,
					    &dentry->d_name, 0, NULL,
					    EXT4_HT_DIR, credits);
	handle = ext4_journal_current_handle();
	if (IS_ERR(inode)) {
		if (handle)
			ext4_journal_stop(handle);
		return PTR_ERR(inode);
	}

	if (IS_ENCRYPTED(inode)) {
		err = fscrypt_encrypt_symlink(inode, symname, len, &disk_link);
		if (err)
			goto err_drop_inode;
		inode->i_op = &ext4_encrypted_symlink_inode_operations;
	}

	if ((disk_link.len > EXT4_N_BLOCKS * 4)) {
		if (!IS_ENCRYPTED(inode))
			inode->i_op = &ext4_symlink_inode_operations;
		inode_nohighmem(inode);
		ext4_set_aops(inode);
		/*
		 * We cannot call page_symlink() with transaction started
		 * because it calls into ext4_write_begin() which can wait
		 * for transaction commit if we are running out of space
		 * and thus we deadlock. So we have to stop transaction now
		 * and restart it when symlink contents is written.
		 * 
		 * To keep fs consistent in case of crash, we have to put inode
		 * to orphan list in the mean time.
		 */
		drop_nlink(inode);
		err = ext4_orphan_add(handle, inode);
		ext4_journal_stop(handle);
		handle = NULL;
		if (err)
			goto err_drop_inode;
		err = __page_symlink(inode, disk_link.name, disk_link.len, 1);
		if (err)
			goto err_drop_inode;
		/*
		 * Now inode is being linked into dir (EXT4_DATA_TRANS_BLOCKS
		 * + EXT4_INDEX_EXTRA_TRANS_BLOCKS), inode is also modified
		 */
		handle = ext4_journal_start(dir, EXT4_HT_DIR,
				EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
				EXT4_INDEX_EXTRA_TRANS_BLOCKS + 1);
		if (IS_ERR(handle)) {
			err = PTR_ERR(handle);
			handle = NULL;
			goto err_drop_inode;
		}
		set_nlink(inode, 1);
		err = ext4_orphan_del(handle, inode);
		if (err)
			goto err_drop_inode;
	} else {
		/* clear the extent format for fast symlink */
		ext4_clear_inode_flag(inode, EXT4_INODE_EXTENTS);
		if (!IS_ENCRYPTED(inode)) {
			inode->i_op = &ext4_fast_symlink_inode_operations;
			inode->i_link = (char *)&EXT4_I(inode)->i_data;
		}
		memcpy((char *)&EXT4_I(inode)->i_data, disk_link.name,
		       disk_link.len);
		inode->i_size = disk_link.len - 1;
	}
	EXT4_I(inode)->i_disksize = inode->i_size;
	err = ext4_add_nondir(handle, dentry, inode);
	if (!err && IS_DIRSYNC(dir))
		ext4_handle_sync(handle);

	if (handle)
		ext4_journal_stop(handle);
	goto out_free_encrypted_link;

err_drop_inode:
	if (handle)
		ext4_journal_stop(handle);
	clear_nlink(inode);
	unlock_new_inode(inode);
	iput(inode);
out_free_encrypted_link:
	if (disk_link.name != (unsigned char *)symname)
		kfree(disk_link.name);
	return err;
}