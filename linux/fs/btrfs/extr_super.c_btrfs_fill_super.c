#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int s_time_gran; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_iflags; int /*<<< orphan*/  s_xattr; int /*<<< orphan*/ * s_export_op; int /*<<< orphan*/ * s_d_op; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_maxbytes; } ;
struct inode {int dummy; } ;
struct btrfs_key {scalar_t__ offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_fs_info {int /*<<< orphan*/  fs_root; } ;
struct btrfs_fs_devices {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FIRST_FREE_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_INODE_ITEM_KEY ; 
 int /*<<< orphan*/  BTRFS_SUPER_MAGIC ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  SB_ACTIVE ; 
 int /*<<< orphan*/  SB_I_CGROUPWB ; 
 int /*<<< orphan*/  SB_I_VERSION ; 
 int /*<<< orphan*/  SB_POSIXACL ; 
 int /*<<< orphan*/  btrfs_dentry_operations ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*) ; 
 int /*<<< orphan*/  btrfs_export_ops ; 
 struct inode* btrfs_iget (struct super_block*,struct btrfs_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btrfs_fs_info* btrfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  btrfs_super_ops ; 
 int /*<<< orphan*/  btrfs_xattr_handlers ; 
 int /*<<< orphan*/  cleancache_init_fs (struct super_block*) ; 
 int /*<<< orphan*/  close_ctree (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int open_ctree (struct super_block*,struct btrfs_fs_devices*,char*) ; 
 int super_setup_bdi (struct super_block*) ; 

__attribute__((used)) static int btrfs_fill_super(struct super_block *sb,
			    struct btrfs_fs_devices *fs_devices,
			    void *data)
{
	struct inode *inode;
	struct btrfs_fs_info *fs_info = btrfs_sb(sb);
	struct btrfs_key key;
	int err;

	sb->s_maxbytes = MAX_LFS_FILESIZE;
	sb->s_magic = BTRFS_SUPER_MAGIC;
	sb->s_op = &btrfs_super_ops;
	sb->s_d_op = &btrfs_dentry_operations;
	sb->s_export_op = &btrfs_export_ops;
	sb->s_xattr = btrfs_xattr_handlers;
	sb->s_time_gran = 1;
#ifdef CONFIG_BTRFS_FS_POSIX_ACL
	sb->s_flags |= SB_POSIXACL;
#endif
	sb->s_flags |= SB_I_VERSION;
	sb->s_iflags |= SB_I_CGROUPWB;

	err = super_setup_bdi(sb);
	if (err) {
		btrfs_err(fs_info, "super_setup_bdi failed");
		return err;
	}

	err = open_ctree(sb, fs_devices, (char *)data);
	if (err) {
		btrfs_err(fs_info, "open_ctree failed");
		return err;
	}

	key.objectid = BTRFS_FIRST_FREE_OBJECTID;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;
	inode = btrfs_iget(sb, &key, fs_info->fs_root, NULL);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto fail_close;
	}

	sb->s_root = d_make_root(inode);
	if (!sb->s_root) {
		err = -ENOMEM;
		goto fail_close;
	}

	cleancache_init_fs(sb);
	sb->s_flags |= SB_ACTIVE;
	return 0;

fail_close:
	close_ctree(fs_info);
	return err;
}