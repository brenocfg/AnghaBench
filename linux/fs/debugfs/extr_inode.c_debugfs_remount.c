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
struct super_block {struct debugfs_fs_info* s_fs_info; } ;
struct debugfs_fs_info {int /*<<< orphan*/  mount_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_apply_options (struct super_block*) ; 
 int debugfs_parse_options (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_filesystem (struct super_block*) ; 

__attribute__((used)) static int debugfs_remount(struct super_block *sb, int *flags, char *data)
{
	int err;
	struct debugfs_fs_info *fsi = sb->s_fs_info;

	sync_filesystem(sb);
	err = debugfs_parse_options(data, &fsi->mount_opts);
	if (err)
		goto fail;

	debugfs_apply_options(sb);

fail:
	return err;
}