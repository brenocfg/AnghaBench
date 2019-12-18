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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct f2fs_sb_info {scalar_t__ gc_mode; int /*<<< orphan*/  sb; } ;
struct discard_policy {unsigned int max_interval; unsigned int min_interval; unsigned int mid_interval; } ;
struct discard_cmd_control {int discard_granularity; int /*<<< orphan*/  queued_discard; scalar_t__ discard_wake; int /*<<< orphan*/  discard_wait_queue; } ;
struct TYPE_2__ {struct discard_cmd_control* dcc_info; } ;

/* Variables and functions */
 unsigned int DEF_MIN_DISCARD_ISSUE_TIME ; 
 int /*<<< orphan*/  DISCARD_TIME ; 
 int /*<<< orphan*/  DPOLICY_BG ; 
 int /*<<< orphan*/  DPOLICY_FORCE ; 
 scalar_t__ GC_URGENT ; 
 int /*<<< orphan*/  SBI_NEED_FSCK ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __init_discard_policy (struct f2fs_sb_info*,struct discard_policy*,int /*<<< orphan*/ ,int) ; 
 int __issue_discard_cmd (struct f2fs_sb_info*,struct discard_policy*) ; 
 int /*<<< orphan*/  __wait_all_discard_cmd (struct f2fs_sb_info*,struct discard_policy*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ f2fs_readonly (int /*<<< orphan*/ ) ; 
 unsigned int f2fs_time_to_wait (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ freezing (int /*<<< orphan*/ ) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 scalar_t__ try_to_freeze () ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int issue_discard_thread(void *data)
{
	struct f2fs_sb_info *sbi = data;
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	wait_queue_head_t *q = &dcc->discard_wait_queue;
	struct discard_policy dpolicy;
	unsigned int wait_ms = DEF_MIN_DISCARD_ISSUE_TIME;
	int issued;

	set_freezable();

	do {
		__init_discard_policy(sbi, &dpolicy, DPOLICY_BG,
					dcc->discard_granularity);

		wait_event_interruptible_timeout(*q,
				kthread_should_stop() || freezing(current) ||
				dcc->discard_wake,
				msecs_to_jiffies(wait_ms));

		if (dcc->discard_wake)
			dcc->discard_wake = 0;

		/* clean up pending candidates before going to sleep */
		if (atomic_read(&dcc->queued_discard))
			__wait_all_discard_cmd(sbi, NULL);

		if (try_to_freeze())
			continue;
		if (f2fs_readonly(sbi->sb))
			continue;
		if (kthread_should_stop())
			return 0;
		if (is_sbi_flag_set(sbi, SBI_NEED_FSCK)) {
			wait_ms = dpolicy.max_interval;
			continue;
		}

		if (sbi->gc_mode == GC_URGENT)
			__init_discard_policy(sbi, &dpolicy, DPOLICY_FORCE, 1);

		sb_start_intwrite(sbi->sb);

		issued = __issue_discard_cmd(sbi, &dpolicy);
		if (issued > 0) {
			__wait_all_discard_cmd(sbi, &dpolicy);
			wait_ms = dpolicy.min_interval;
		} else if (issued == -1){
			wait_ms = f2fs_time_to_wait(sbi, DISCARD_TIME);
			if (!wait_ms)
				wait_ms = dpolicy.mid_interval;
		} else {
			wait_ms = dpolicy.max_interval;
		}

		sb_end_intwrite(sbi->sb);

	} while (!kthread_should_stop());
	return 0;
}