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
struct super_block {int dummy; } ;
struct pts_mount_opts {int dummy; } ;
struct pts_fs_info {struct pts_mount_opts mount_opts; } ;

/* Variables and functions */
 struct pts_fs_info* DEVPTS_SB (struct super_block*) ; 
 int /*<<< orphan*/  PARSE_REMOUNT ; 
 int parse_mount_options (char*,int /*<<< orphan*/ ,struct pts_mount_opts*) ; 
 int /*<<< orphan*/  update_ptmx_mode (struct pts_fs_info*) ; 

__attribute__((used)) static int devpts_remount(struct super_block *sb, int *flags, char *data)
{
	int err;
	struct pts_fs_info *fsi = DEVPTS_SB(sb);
	struct pts_mount_opts *opts = &fsi->mount_opts;

	err = parse_mount_options(data, PARSE_REMOUNT, opts);

	/*
	 * parse_mount_options() restores options to default values
	 * before parsing and may have changed ptmxmode. So, update the
	 * mode in the inode too. Bogus options don't fail the remount,
	 * so do this even on error return.
	 */
	update_ptmx_mode(fsi);

	return err;
}