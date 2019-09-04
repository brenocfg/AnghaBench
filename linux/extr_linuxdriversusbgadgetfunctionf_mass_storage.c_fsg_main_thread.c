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
struct fsg_lun {int dummy; } ;
struct fsg_common {scalar_t__ state; int /*<<< orphan*/  thread_notifier; int /*<<< orphan*/  filesem; struct fsg_lun** luns; int /*<<< orphan*/  lock; int /*<<< orphan*/ * thread_task; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct fsg_lun**) ; 
 scalar_t__ FSG_STATE_TERMINATED ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  allow_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_and_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ do_scsi_command (struct fsg_common*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ exception_in_progress (struct fsg_common*) ; 
 scalar_t__ finish_reply (struct fsg_common*) ; 
 int /*<<< orphan*/  fsg_lun_close (struct fsg_lun*) ; 
 scalar_t__ fsg_lun_is_open (struct fsg_lun*) ; 
 scalar_t__ get_next_command (struct fsg_common*) ; 
 int /*<<< orphan*/  handle_exception (struct fsg_common*) ; 
 int /*<<< orphan*/  send_status (struct fsg_common*) ; 
 int /*<<< orphan*/  set_freezable () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep_thread (struct fsg_common*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsg_main_thread(void *common_)
{
	struct fsg_common	*common = common_;
	int			i;

	/*
	 * Allow the thread to be killed by a signal, but set the signal mask
	 * to block everything but INT, TERM, KILL, and USR1.
	 */
	allow_signal(SIGINT);
	allow_signal(SIGTERM);
	allow_signal(SIGKILL);
	allow_signal(SIGUSR1);

	/* Allow the thread to be frozen */
	set_freezable();

	/* The main loop */
	while (common->state != FSG_STATE_TERMINATED) {
		if (exception_in_progress(common) || signal_pending(current)) {
			handle_exception(common);
			continue;
		}

		if (!common->running) {
			sleep_thread(common, true, NULL);
			continue;
		}

		if (get_next_command(common) || exception_in_progress(common))
			continue;
		if (do_scsi_command(common) || exception_in_progress(common))
			continue;
		if (finish_reply(common) || exception_in_progress(common))
			continue;
		send_status(common);
	}

	spin_lock_irq(&common->lock);
	common->thread_task = NULL;
	spin_unlock_irq(&common->lock);

	/* Eject media from all LUNs */

	down_write(&common->filesem);
	for (i = 0; i < ARRAY_SIZE(common->luns); i++) {
		struct fsg_lun *curlun = common->luns[i];

		if (curlun && fsg_lun_is_open(curlun))
			fsg_lun_close(curlun);
	}
	up_write(&common->filesem);

	/* Let fsg_unbind() know the thread has exited */
	complete_and_exit(&common->thread_notifier, 0);
}