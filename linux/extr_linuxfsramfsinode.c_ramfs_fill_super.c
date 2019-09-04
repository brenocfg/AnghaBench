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
struct super_block {int s_time_gran; int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_maxbytes; struct ramfs_fs_info* s_fs_info; } ;
struct TYPE_2__ {int mode; } ;
struct ramfs_fs_info {TYPE_1__ mount_opts; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RAMFS_MAGIC ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 struct ramfs_fs_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct inode* ramfs_get_inode (struct super_block*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ramfs_ops ; 
 int ramfs_parse_options (void*,TYPE_1__*) ; 

int ramfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct ramfs_fs_info *fsi;
	struct inode *inode;
	int err;

	fsi = kzalloc(sizeof(struct ramfs_fs_info), GFP_KERNEL);
	sb->s_fs_info = fsi;
	if (!fsi)
		return -ENOMEM;

	err = ramfs_parse_options(data, &fsi->mount_opts);
	if (err)
		return err;

	sb->s_maxbytes		= MAX_LFS_FILESIZE;
	sb->s_blocksize		= PAGE_SIZE;
	sb->s_blocksize_bits	= PAGE_SHIFT;
	sb->s_magic		= RAMFS_MAGIC;
	sb->s_op		= &ramfs_ops;
	sb->s_time_gran		= 1;

	inode = ramfs_get_inode(sb, NULL, S_IFDIR | fsi->mount_opts.mode, 0);
	sb->s_root = d_make_root(inode);
	if (!sb->s_root)
		return -ENOMEM;

	return 0;
}