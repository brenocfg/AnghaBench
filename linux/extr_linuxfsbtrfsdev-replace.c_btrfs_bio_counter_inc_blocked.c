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
struct btrfs_fs_info {int /*<<< orphan*/  fs_state; int /*<<< orphan*/  replace_wait; int /*<<< orphan*/  bio_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_STATE_DEV_REPLACING ; 
 int /*<<< orphan*/  btrfs_bio_counter_dec (struct btrfs_fs_info*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void btrfs_bio_counter_inc_blocked(struct btrfs_fs_info *fs_info)
{
	while (1) {
		percpu_counter_inc(&fs_info->bio_counter);
		if (likely(!test_bit(BTRFS_FS_STATE_DEV_REPLACING,
				     &fs_info->fs_state)))
			break;

		btrfs_bio_counter_dec(fs_info);
		wait_event(fs_info->replace_wait,
			   !test_bit(BTRFS_FS_STATE_DEV_REPLACING,
				     &fs_info->fs_state));
	}
}