#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  c_line; } ;
struct tty_struct {TYPE_3__ termios; scalar_t__ ldisc; TYPE_2__* driver; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  flags; } ;
struct tty_ldisc {TYPE_1__* ops; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hangup ) (struct tty_struct*) ;int /*<<< orphan*/  (* write_wakeup ) (struct tty_struct*) ;int /*<<< orphan*/  (* flush_buffer ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLLOUT ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  N_NULL ; 
 int /*<<< orphan*/  N_TTY ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int TTY_DRIVER_RESET_TERMIOS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  stub2 (struct tty_struct*) ; 
 int /*<<< orphan*/  stub3 (struct tty_struct*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_debug (struct tty_struct*,char*,scalar_t__) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_kill (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_lock (struct tty_struct*,int /*<<< orphan*/ ) ; 
 struct tty_ldisc* tty_ldisc_ref (struct tty_struct*) ; 
 scalar_t__ tty_ldisc_reinit (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_ldisc_unlock (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_reset_termios (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tty_ldisc_hangup(struct tty_struct *tty, bool reinit)
{
	struct tty_ldisc *ld;

	tty_ldisc_debug(tty, "%p: hangup\n", tty->ldisc);

	ld = tty_ldisc_ref(tty);
	if (ld != NULL) {
		if (ld->ops->flush_buffer)
			ld->ops->flush_buffer(tty);
		tty_driver_flush_buffer(tty);
		if ((test_bit(TTY_DO_WRITE_WAKEUP, &tty->flags)) &&
		    ld->ops->write_wakeup)
			ld->ops->write_wakeup(tty);
		if (ld->ops->hangup)
			ld->ops->hangup(tty);
		tty_ldisc_deref(ld);
	}

	wake_up_interruptible_poll(&tty->write_wait, EPOLLOUT);
	wake_up_interruptible_poll(&tty->read_wait, EPOLLIN);

	/*
	 * Shutdown the current line discipline, and reset it to
	 * N_TTY if need be.
	 *
	 * Avoid racing set_ldisc or tty_ldisc_release
	 */
	tty_ldisc_lock(tty, MAX_SCHEDULE_TIMEOUT);

	if (tty->driver->flags & TTY_DRIVER_RESET_TERMIOS)
		tty_reset_termios(tty);

	if (tty->ldisc) {
		if (reinit) {
			if (tty_ldisc_reinit(tty, tty->termios.c_line) < 0 &&
			    tty_ldisc_reinit(tty, N_TTY) < 0)
				WARN_ON(tty_ldisc_reinit(tty, N_NULL) < 0);
		} else
			tty_ldisc_kill(tty);
	}
	tty_ldisc_unlock(tty);
}