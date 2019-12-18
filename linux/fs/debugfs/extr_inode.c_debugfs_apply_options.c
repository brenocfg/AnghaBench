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
struct super_block {int /*<<< orphan*/  s_root; struct debugfs_fs_info* s_fs_info; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
struct debugfs_mount_opts {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; } ;
struct debugfs_fs_info {struct debugfs_mount_opts mount_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IALLUGO ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int debugfs_apply_options(struct super_block *sb)
{
	struct debugfs_fs_info *fsi = sb->s_fs_info;
	struct inode *inode = d_inode(sb->s_root);
	struct debugfs_mount_opts *opts = &fsi->mount_opts;

	inode->i_mode &= ~S_IALLUGO;
	inode->i_mode |= opts->mode;

	inode->i_uid = opts->uid;
	inode->i_gid = opts->gid;

	return 0;
}