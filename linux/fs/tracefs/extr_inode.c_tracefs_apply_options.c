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
struct tracefs_mount_opts {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; } ;
struct tracefs_fs_info {struct tracefs_mount_opts mount_opts; } ;
struct super_block {TYPE_1__* s_root; struct tracefs_fs_info* s_fs_info; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IALLUGO ; 

__attribute__((used)) static int tracefs_apply_options(struct super_block *sb)
{
	struct tracefs_fs_info *fsi = sb->s_fs_info;
	struct inode *inode = sb->s_root->d_inode;
	struct tracefs_mount_opts *opts = &fsi->mount_opts;

	inode->i_mode &= ~S_IALLUGO;
	inode->i_mode |= opts->mode;

	inode->i_uid = opts->uid;
	inode->i_gid = opts->gid;

	return 0;
}