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
 int /*<<< orphan*/  WB_REASON_SYNC ; 
 int /*<<< orphan*/  fdatawait_one_bdev ; 
 int /*<<< orphan*/  fdatawrite_one_bdev ; 
 int /*<<< orphan*/  iterate_bdevs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterate_supers (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  laptop_mode ; 
 int /*<<< orphan*/  laptop_sync_completion () ; 
 int /*<<< orphan*/  sync_fs_one_sb ; 
 int /*<<< orphan*/  sync_inodes_one_sb ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_flusher_threads (int /*<<< orphan*/ ) ; 

void ksys_sync(void)
{
	int nowait = 0, wait = 1;

	wakeup_flusher_threads(WB_REASON_SYNC);
	iterate_supers(sync_inodes_one_sb, NULL);
	iterate_supers(sync_fs_one_sb, &nowait);
	iterate_supers(sync_fs_one_sb, &wait);
	iterate_bdevs(fdatawrite_one_bdev, NULL);
	iterate_bdevs(fdatawait_one_bdev, NULL);
	if (unlikely(laptop_mode))
		laptop_sync_completion();
}