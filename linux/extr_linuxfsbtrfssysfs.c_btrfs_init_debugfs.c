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

/* Variables and functions */

__attribute__((used)) static int btrfs_init_debugfs(void)
{
#ifdef CONFIG_DEBUG_FS
	btrfs_debugfs_root_dentry = debugfs_create_dir("btrfs", NULL);
	if (!btrfs_debugfs_root_dentry)
		return -ENOMEM;

	/*
	 * Example code, how to export data through debugfs.
	 *
	 * file:        /sys/kernel/debug/btrfs/test
	 * contents of: btrfs_debugfs_test
	 */
#ifdef CONFIG_BTRFS_DEBUG
	debugfs_create_u64("test", S_IRUGO | S_IWUSR, btrfs_debugfs_root_dentry,
			&btrfs_debugfs_test);
#endif

#endif
	return 0;
}