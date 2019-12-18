#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct f2fs_sb_info {scalar_t__ gc_mode; TYPE_2__* sb; int /*<<< orphan*/  gc_mutex; struct f2fs_gc_kthread* gc_thread; } ;
struct f2fs_gc_kthread {unsigned int min_sleep_time; unsigned int urgent_sleep_time; unsigned int no_gc_sleep_time; scalar_t__ gc_wake; int /*<<< orphan*/  gc_wait_queue_head; } ;
struct TYPE_5__ {scalar_t__ frozen; } ;
struct TYPE_6__ {TYPE_1__ s_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAULT_CHECKPOINT ; 
 int /*<<< orphan*/  FORCE_FG_GC ; 
 int /*<<< orphan*/  GC_TIME ; 
 scalar_t__ GC_URGENT ; 
 int /*<<< orphan*/  NULL_SEGNO ; 
 scalar_t__ SB_FREEZE_WRITE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  decrease_sleep_time (struct f2fs_gc_kthread*,unsigned int*) ; 
 int /*<<< orphan*/  f2fs_balance_fs_bg (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_gc (struct f2fs_sb_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_stop_checkpoint (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  free_segments (struct f2fs_sb_info*) ; 
 scalar_t__ freezing (int /*<<< orphan*/ ) ; 
 scalar_t__ has_enough_invalid_blocks (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  increase_sleep_time (struct f2fs_gc_kthread*,unsigned int*) ; 
 int /*<<< orphan*/  is_idle (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefree_segments (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  sb_end_write (TYPE_2__*) ; 
 int /*<<< orphan*/  sb_start_write_trylock (TYPE_2__*) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  stat_inc_bggc_count (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  stat_io_skip_bggc_count (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  stat_other_skip_bggc_count (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_to_inject (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_background_gc (TYPE_2__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ try_to_freeze () ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gc_thread_func(void *data)
{
	struct f2fs_sb_info *sbi = data;
	struct f2fs_gc_kthread *gc_th = sbi->gc_thread;
	wait_queue_head_t *wq = &sbi->gc_thread->gc_wait_queue_head;
	unsigned int wait_ms;

	wait_ms = gc_th->min_sleep_time;

	set_freezable();
	do {
		wait_event_interruptible_timeout(*wq,
				kthread_should_stop() || freezing(current) ||
				gc_th->gc_wake,
				msecs_to_jiffies(wait_ms));

		/* give it a try one time */
		if (gc_th->gc_wake)
			gc_th->gc_wake = 0;

		if (try_to_freeze()) {
			stat_other_skip_bggc_count(sbi);
			continue;
		}
		if (kthread_should_stop())
			break;

		if (sbi->sb->s_writers.frozen >= SB_FREEZE_WRITE) {
			increase_sleep_time(gc_th, &wait_ms);
			stat_other_skip_bggc_count(sbi);
			continue;
		}

		if (time_to_inject(sbi, FAULT_CHECKPOINT)) {
			f2fs_show_injection_info(FAULT_CHECKPOINT);
			f2fs_stop_checkpoint(sbi, false);
		}

		if (!sb_start_write_trylock(sbi->sb)) {
			stat_other_skip_bggc_count(sbi);
			continue;
		}

		/*
		 * [GC triggering condition]
		 * 0. GC is not conducted currently.
		 * 1. There are enough dirty segments.
		 * 2. IO subsystem is idle by checking the # of writeback pages.
		 * 3. IO subsystem is idle by checking the # of requests in
		 *    bdev's request list.
		 *
		 * Note) We have to avoid triggering GCs frequently.
		 * Because it is possible that some segments can be
		 * invalidated soon after by user update or deletion.
		 * So, I'd like to wait some time to collect dirty segments.
		 */
		if (sbi->gc_mode == GC_URGENT) {
			wait_ms = gc_th->urgent_sleep_time;
			mutex_lock(&sbi->gc_mutex);
			goto do_gc;
		}

		if (!mutex_trylock(&sbi->gc_mutex)) {
			stat_other_skip_bggc_count(sbi);
			goto next;
		}

		if (!is_idle(sbi, GC_TIME)) {
			increase_sleep_time(gc_th, &wait_ms);
			mutex_unlock(&sbi->gc_mutex);
			stat_io_skip_bggc_count(sbi);
			goto next;
		}

		if (has_enough_invalid_blocks(sbi))
			decrease_sleep_time(gc_th, &wait_ms);
		else
			increase_sleep_time(gc_th, &wait_ms);
do_gc:
		stat_inc_bggc_count(sbi);

		/* if return value is not zero, no victim was selected */
		if (f2fs_gc(sbi, test_opt(sbi, FORCE_FG_GC), true, NULL_SEGNO))
			wait_ms = gc_th->no_gc_sleep_time;

		trace_f2fs_background_gc(sbi->sb, wait_ms,
				prefree_segments(sbi), free_segments(sbi));

		/* balancing f2fs's metadata periodically */
		f2fs_balance_fs_bg(sbi);
next:
		sb_end_write(sbi->sb);

	} while (!kthread_should_stop());
	return 0;
}