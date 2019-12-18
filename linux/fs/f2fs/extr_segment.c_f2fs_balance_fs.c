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
struct f2fs_sb_info {int /*<<< orphan*/  gc_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAULT_CHECKPOINT ; 
 int /*<<< orphan*/  NULL_SEGNO ; 
 scalar_t__ excess_cached_nats (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_balance_fs_bg (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_gc (struct f2fs_sb_info*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_is_checkpoint_ready (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_stop_checkpoint (struct f2fs_sb_info*,int) ; 
 scalar_t__ has_not_enough_free_secs (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_to_inject (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

void f2fs_balance_fs(struct f2fs_sb_info *sbi, bool need)
{
	if (time_to_inject(sbi, FAULT_CHECKPOINT)) {
		f2fs_show_injection_info(FAULT_CHECKPOINT);
		f2fs_stop_checkpoint(sbi, false);
	}

	/* balance_fs_bg is able to be pending */
	if (need && excess_cached_nats(sbi))
		f2fs_balance_fs_bg(sbi);

	if (!f2fs_is_checkpoint_ready(sbi))
		return;

	/*
	 * We should do GC or end up with checkpoint, if there are so many dirty
	 * dir/node pages without enough free segments.
	 */
	if (has_not_enough_free_secs(sbi, 0, 0)) {
		mutex_lock(&sbi->gc_mutex);
		f2fs_gc(sbi, false, false, NULL_SEGNO);
	}
}