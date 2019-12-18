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
struct TYPE_2__ {int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ubi_num; } ;
struct ubifs_info {scalar_t__ max_inode_sz; struct inode* ubi; int /*<<< orphan*/  umount_mutex; TYPE_1__ vi; struct super_block* vfs_sb; } ;
struct super_block {scalar_t__ s_maxbytes; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_xattr; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_magic; struct ubifs_info* s_fs_info; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ MAX_LFS_FILESIZE ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  UBIFS_BLOCK_SHIFT ; 
 int /*<<< orphan*/  UBIFS_BLOCK_SIZE ; 
 int /*<<< orphan*/  UBIFS_ROOT_INO ; 
 int /*<<< orphan*/  UBIFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  UBI_READWRITE ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int /*<<< orphan*/  fscrypt_set_ops (struct super_block*,int /*<<< orphan*/ *) ; 
 scalar_t__ key_max_inode_size (struct ubifs_info*) ; 
 int mount_ubifs (struct ubifs_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int super_setup_bdi_name (struct super_block*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_close_volume (struct inode*) ; 
 struct inode* ubi_open_volume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_crypt_operations ; 
 struct inode* ubifs_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 int ubifs_parse_options (struct ubifs_info*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_super_operations ; 
 int /*<<< orphan*/  ubifs_umount (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_xattr_handlers ; 

__attribute__((used)) static int ubifs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct ubifs_info *c = sb->s_fs_info;
	struct inode *root;
	int err;

	c->vfs_sb = sb;
	/* Re-open the UBI device in read-write mode */
	c->ubi = ubi_open_volume(c->vi.ubi_num, c->vi.vol_id, UBI_READWRITE);
	if (IS_ERR(c->ubi)) {
		err = PTR_ERR(c->ubi);
		goto out;
	}

	err = ubifs_parse_options(c, data, 0);
	if (err)
		goto out_close;

	/*
	 * UBIFS provides 'backing_dev_info' in order to disable read-ahead. For
	 * UBIFS, I/O is not deferred, it is done immediately in readpage,
	 * which means the user would have to wait not just for their own I/O
	 * but the read-ahead I/O as well i.e. completely pointless.
	 *
	 * Read-ahead will be disabled because @sb->s_bdi->ra_pages is 0. Also
	 * @sb->s_bdi->capabilities are initialized to 0 so there won't be any
	 * writeback happening.
	 */
	err = super_setup_bdi_name(sb, "ubifs_%d_%d", c->vi.ubi_num,
				   c->vi.vol_id);
	if (err)
		goto out_close;

	sb->s_fs_info = c;
	sb->s_magic = UBIFS_SUPER_MAGIC;
	sb->s_blocksize = UBIFS_BLOCK_SIZE;
	sb->s_blocksize_bits = UBIFS_BLOCK_SHIFT;
	sb->s_maxbytes = c->max_inode_sz = key_max_inode_size(c);
	if (c->max_inode_sz > MAX_LFS_FILESIZE)
		sb->s_maxbytes = c->max_inode_sz = MAX_LFS_FILESIZE;
	sb->s_op = &ubifs_super_operations;
#ifdef CONFIG_UBIFS_FS_XATTR
	sb->s_xattr = ubifs_xattr_handlers;
#endif
	fscrypt_set_ops(sb, &ubifs_crypt_operations);

	mutex_lock(&c->umount_mutex);
	err = mount_ubifs(c);
	if (err) {
		ubifs_assert(c, err < 0);
		goto out_unlock;
	}

	/* Read the root inode */
	root = ubifs_iget(sb, UBIFS_ROOT_INO);
	if (IS_ERR(root)) {
		err = PTR_ERR(root);
		goto out_umount;
	}

	sb->s_root = d_make_root(root);
	if (!sb->s_root) {
		err = -ENOMEM;
		goto out_umount;
	}

	mutex_unlock(&c->umount_mutex);
	return 0;

out_umount:
	ubifs_umount(c);
out_unlock:
	mutex_unlock(&c->umount_mutex);
out_close:
	ubi_close_volume(c->ubi);
out:
	return err;
}