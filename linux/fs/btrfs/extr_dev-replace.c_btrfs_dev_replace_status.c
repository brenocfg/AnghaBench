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
struct TYPE_2__ {int /*<<< orphan*/  progress_1000; void* num_uncorrectable_read_errors; void* num_write_errors; int /*<<< orphan*/  time_stopped; int /*<<< orphan*/  time_started; int /*<<< orphan*/  replace_state; } ;
struct btrfs_ioctl_dev_replace_args {TYPE_1__ status; int /*<<< orphan*/  result; } ;
struct btrfs_dev_replace {int /*<<< orphan*/  rwsem; int /*<<< orphan*/  num_uncorrectable_read_errors; int /*<<< orphan*/  num_write_errors; int /*<<< orphan*/  time_stopped; int /*<<< orphan*/  time_started; int /*<<< orphan*/  replace_state; } ;
struct btrfs_fs_info {struct btrfs_dev_replace dev_replace; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR ; 
 void* atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_dev_replace_progress (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void btrfs_dev_replace_status(struct btrfs_fs_info *fs_info,
			      struct btrfs_ioctl_dev_replace_args *args)
{
	struct btrfs_dev_replace *dev_replace = &fs_info->dev_replace;

	down_read(&dev_replace->rwsem);
	/* even if !dev_replace_is_valid, the values are good enough for
	 * the replace_status ioctl */
	args->result = BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR;
	args->status.replace_state = dev_replace->replace_state;
	args->status.time_started = dev_replace->time_started;
	args->status.time_stopped = dev_replace->time_stopped;
	args->status.num_write_errors =
		atomic64_read(&dev_replace->num_write_errors);
	args->status.num_uncorrectable_read_errors =
		atomic64_read(&dev_replace->num_uncorrectable_read_errors);
	args->status.progress_1000 = btrfs_dev_replace_progress(fs_info);
	up_read(&dev_replace->rwsem);
}