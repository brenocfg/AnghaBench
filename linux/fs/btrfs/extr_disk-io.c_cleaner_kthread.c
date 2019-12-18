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
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  cleaner_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_CLEANER_RUNNING ; 
 int /*<<< orphan*/  BTRFS_FS_OPEN ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int btrfs_clean_one_deleted_snapshot (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_delete_unused_bgs (struct btrfs_fs_info*) ; 
 scalar_t__ btrfs_need_cleaner_sleep (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_run_defrag_inodes (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_run_delayed_iputs (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_parkme () ; 
 scalar_t__ kthread_should_park () ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cleaner_kthread(void *arg)
{
	struct btrfs_root *root = arg;
	struct btrfs_fs_info *fs_info = root->fs_info;
	int again;

	while (1) {
		again = 0;

		set_bit(BTRFS_FS_CLEANER_RUNNING, &fs_info->flags);

		/* Make the cleaner go to sleep early. */
		if (btrfs_need_cleaner_sleep(fs_info))
			goto sleep;

		/*
		 * Do not do anything if we might cause open_ctree() to block
		 * before we have finished mounting the filesystem.
		 */
		if (!test_bit(BTRFS_FS_OPEN, &fs_info->flags))
			goto sleep;

		if (!mutex_trylock(&fs_info->cleaner_mutex))
			goto sleep;

		/*
		 * Avoid the problem that we change the status of the fs
		 * during the above check and trylock.
		 */
		if (btrfs_need_cleaner_sleep(fs_info)) {
			mutex_unlock(&fs_info->cleaner_mutex);
			goto sleep;
		}

		btrfs_run_delayed_iputs(fs_info);

		again = btrfs_clean_one_deleted_snapshot(root);
		mutex_unlock(&fs_info->cleaner_mutex);

		/*
		 * The defragger has dealt with the R/O remount and umount,
		 * needn't do anything special here.
		 */
		btrfs_run_defrag_inodes(fs_info);

		/*
		 * Acquires fs_info->delete_unused_bgs_mutex to avoid racing
		 * with relocation (btrfs_relocate_chunk) and relocation
		 * acquires fs_info->cleaner_mutex (btrfs_relocate_block_group)
		 * after acquiring fs_info->delete_unused_bgs_mutex. So we
		 * can't hold, nor need to, fs_info->cleaner_mutex when deleting
		 * unused block groups.
		 */
		btrfs_delete_unused_bgs(fs_info);
sleep:
		clear_bit(BTRFS_FS_CLEANER_RUNNING, &fs_info->flags);
		if (kthread_should_park())
			kthread_parkme();
		if (kthread_should_stop())
			return 0;
		if (!again) {
			set_current_state(TASK_INTERRUPTIBLE);
			schedule();
			__set_current_state(TASK_RUNNING);
		}
	}
}