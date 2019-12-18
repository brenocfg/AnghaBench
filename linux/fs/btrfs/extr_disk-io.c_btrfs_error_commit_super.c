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
struct btrfs_fs_info {int /*<<< orphan*/  cleanup_work_sem; int /*<<< orphan*/  cleaner_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_cleanup_transaction (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_run_delayed_iputs (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_error_commit_super(struct btrfs_fs_info *fs_info)
{
	/* cleanup FS via transaction */
	btrfs_cleanup_transaction(fs_info);

	mutex_lock(&fs_info->cleaner_mutex);
	btrfs_run_delayed_iputs(fs_info);
	mutex_unlock(&fs_info->cleaner_mutex);

	down_write(&fs_info->cleanup_work_sem);
	up_write(&fs_info->cleanup_work_sem);
}