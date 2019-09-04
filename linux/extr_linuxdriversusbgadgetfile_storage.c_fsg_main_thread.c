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
struct fsg_dev {scalar_t__ state; int /*<<< orphan*/  thread_notifier; int /*<<< orphan*/  atomic_bitflags; int /*<<< orphan*/  lock; int /*<<< orphan*/ * thread_task; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 scalar_t__ FSG_STATE_DATA_PHASE ; 
 scalar_t__ FSG_STATE_IDLE ; 
 scalar_t__ FSG_STATE_STATUS_PHASE ; 
 scalar_t__ FSG_STATE_TERMINATED ; 
 int /*<<< orphan*/  REGISTERED ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  allow_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_and_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ do_scsi_command (struct fsg_dev*) ; 
 scalar_t__ exception_in_progress (struct fsg_dev*) ; 
 scalar_t__ finish_reply (struct fsg_dev*) ; 
 int /*<<< orphan*/  fsg_driver ; 
 int /*<<< orphan*/  get_ds () ; 
 scalar_t__ get_next_command (struct fsg_dev*) ; 
 int /*<<< orphan*/  handle_exception (struct fsg_dev*) ; 
 scalar_t__ send_status (struct fsg_dev*) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep_thread (struct fsg_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_unregister_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsg_main_thread(void *fsg_)
{
	struct fsg_dev		*fsg = fsg_;

	/* Allow the thread to be killed by a signal, but set the signal mask
	 * to block everything but INT, TERM, KILL, and USR1. */
	allow_signal(SIGINT);
	allow_signal(SIGTERM);
	allow_signal(SIGKILL);
	allow_signal(SIGUSR1);

	/* Allow the thread to be frozen */
	set_freezable();

	/* Arrange for userspace references to be interpreted as kernel
	 * pointers.  That way we can pass a kernel pointer to a routine
	 * that expects a __user pointer and it will work okay. */
	set_fs(get_ds());

	/* The main loop */
	while (fsg->state != FSG_STATE_TERMINATED) {
		if (exception_in_progress(fsg) || signal_pending(current)) {
			handle_exception(fsg);
			continue;
		}

		if (!fsg->running) {
			sleep_thread(fsg);
			continue;
		}

		if (get_next_command(fsg))
			continue;

		spin_lock_irq(&fsg->lock);
		if (!exception_in_progress(fsg))
			fsg->state = FSG_STATE_DATA_PHASE;
		spin_unlock_irq(&fsg->lock);

		if (do_scsi_command(fsg) || finish_reply(fsg))
			continue;

		spin_lock_irq(&fsg->lock);
		if (!exception_in_progress(fsg))
			fsg->state = FSG_STATE_STATUS_PHASE;
		spin_unlock_irq(&fsg->lock);

		if (send_status(fsg))
			continue;

		spin_lock_irq(&fsg->lock);
		if (!exception_in_progress(fsg))
			fsg->state = FSG_STATE_IDLE;
		spin_unlock_irq(&fsg->lock);
		}

	spin_lock_irq(&fsg->lock);
	fsg->thread_task = NULL;
	spin_unlock_irq(&fsg->lock);

	/* If we are exiting because of a signal, unregister the
	 * gadget driver. */
	if (test_and_clear_bit(REGISTERED, &fsg->atomic_bitflags))
		usb_gadget_unregister_driver(&fsg_driver);

	/* Let the unbind and cleanup routines know the thread has exited */
	complete_and_exit(&fsg->thread_notifier, 0);
}