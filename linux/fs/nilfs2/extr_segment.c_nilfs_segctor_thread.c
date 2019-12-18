#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct the_nilfs {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  expires; } ;
struct nilfs_sc_info {int sc_interval; int sc_mjcp_freq; int sc_state; scalar_t__ sc_seq_request; scalar_t__ sc_seq_done; int /*<<< orphan*/  sc_wait_task; int /*<<< orphan*/ * sc_task; int /*<<< orphan*/  sc_state_lock; TYPE_1__ sc_timer; int /*<<< orphan*/  sc_wait_daemon; scalar_t__ sc_flush_request; TYPE_2__* sc_super; void* sc_timer_task; } ;
struct TYPE_4__ {struct the_nilfs* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int NILFS_SEGCTOR_COMMIT ; 
 int NILFS_SEGCTOR_QUIT ; 
 int SC_LSEG_SR ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 void* current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ freezing (void*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  nilfs_msg (TYPE_2__*,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ nilfs_sb_dirty (struct the_nilfs*) ; 
 scalar_t__ nilfs_sb_need_update (struct the_nilfs*) ; 
 int nilfs_segctor_flush_mode (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_segctor_thread_construct (struct nilfs_sc_info*,int) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_nilfs_discontinued (struct the_nilfs*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_segctor_thread(void *arg)
{
	struct nilfs_sc_info *sci = (struct nilfs_sc_info *)arg;
	struct the_nilfs *nilfs = sci->sc_super->s_fs_info;
	int timeout = 0;

	sci->sc_timer_task = current;

	/* start sync. */
	sci->sc_task = current;
	wake_up(&sci->sc_wait_task); /* for nilfs_segctor_start_thread() */
	nilfs_msg(sci->sc_super, KERN_INFO,
		  "segctord starting. Construction interval = %lu seconds, CP frequency < %lu seconds",
		  sci->sc_interval / HZ, sci->sc_mjcp_freq / HZ);

	spin_lock(&sci->sc_state_lock);
 loop:
	for (;;) {
		int mode;

		if (sci->sc_state & NILFS_SEGCTOR_QUIT)
			goto end_thread;

		if (timeout || sci->sc_seq_request != sci->sc_seq_done)
			mode = SC_LSEG_SR;
		else if (sci->sc_flush_request)
			mode = nilfs_segctor_flush_mode(sci);
		else
			break;

		spin_unlock(&sci->sc_state_lock);
		nilfs_segctor_thread_construct(sci, mode);
		spin_lock(&sci->sc_state_lock);
		timeout = 0;
	}


	if (freezing(current)) {
		spin_unlock(&sci->sc_state_lock);
		try_to_freeze();
		spin_lock(&sci->sc_state_lock);
	} else {
		DEFINE_WAIT(wait);
		int should_sleep = 1;

		prepare_to_wait(&sci->sc_wait_daemon, &wait,
				TASK_INTERRUPTIBLE);

		if (sci->sc_seq_request != sci->sc_seq_done)
			should_sleep = 0;
		else if (sci->sc_flush_request)
			should_sleep = 0;
		else if (sci->sc_state & NILFS_SEGCTOR_COMMIT)
			should_sleep = time_before(jiffies,
					sci->sc_timer.expires);

		if (should_sleep) {
			spin_unlock(&sci->sc_state_lock);
			schedule();
			spin_lock(&sci->sc_state_lock);
		}
		finish_wait(&sci->sc_wait_daemon, &wait);
		timeout = ((sci->sc_state & NILFS_SEGCTOR_COMMIT) &&
			   time_after_eq(jiffies, sci->sc_timer.expires));

		if (nilfs_sb_dirty(nilfs) && nilfs_sb_need_update(nilfs))
			set_nilfs_discontinued(nilfs);
	}
	goto loop;

 end_thread:
	spin_unlock(&sci->sc_state_lock);

	/* end sync. */
	sci->sc_task = NULL;
	wake_up(&sci->sc_wait_task); /* for nilfs_segctor_kill_thread() */
	return 0;
}