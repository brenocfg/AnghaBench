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
typedef  int uint ;
struct un_t {int /*<<< orphan*/  un_flags_wait; } ;
struct tty_struct {struct un_t* driver_data; } ;
struct file {int f_flags; } ;
struct TYPE_6__ {int un_flags; } ;
struct TYPE_5__ {int un_flags; } ;
struct channel_t {int ch_flags; int /*<<< orphan*/  ch_lock; int /*<<< orphan*/  ch_wopen; int /*<<< orphan*/  ch_flags_wait; TYPE_3__ ch_pun; TYPE_2__ ch_tun; TYPE_1__* ch_bd; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ BOARD_FAILED ; 
 int CH_CD ; 
 int CH_FCAR ; 
 int EAGAIN ; 
 int EIO ; 
 int ENXIO ; 
 int ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int UN_CLOSING ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 
 scalar_t__ tty_io_error (struct tty_struct*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dgnc_block_til_ready(struct tty_struct *tty,
				struct file *file,
				struct channel_t *ch)
{
	int rc = 0;
	struct un_t *un = tty->driver_data;
	unsigned long flags;
	uint	old_flags = 0;
	int	sleep_on_un_flags = 0;

	if (!file)
		return -ENXIO;

	spin_lock_irqsave(&ch->ch_lock, flags);

	ch->ch_wopen++;

	while (1) {
		sleep_on_un_flags = 0;

		if (ch->ch_bd->state == BOARD_FAILED) {
			rc = -ENXIO;
			break;
		}

		if (tty_hung_up_p(file)) {
			rc = -EAGAIN;
			break;
		}

		/*
		 * If either unit is in the middle of the fragile part of close,
		 * we just cannot touch the channel safely.
		 * Go back to sleep, knowing that when the channel can be
		 * touched safely, the close routine will signal the
		 * ch_wait_flags to wake us back up.
		 */
		if (!((ch->ch_tun.un_flags |
		    ch->ch_pun.un_flags) &
		    UN_CLOSING)) {
			/*
			 * Our conditions to leave cleanly and happily:
			 * 1) NONBLOCKING on the tty is set.
			 * 2) CLOCAL is set.
			 * 3) DCD (fake or real) is active.
			 */

			if (file->f_flags & O_NONBLOCK)
				break;

			if (tty_io_error(tty)) {
				rc = -EIO;
				break;
			}

			if (ch->ch_flags & CH_CD)
				break;

			if (ch->ch_flags & CH_FCAR)
				break;
		} else {
			sleep_on_un_flags = 1;
		}

		/*
		 * If there is a signal pending, the user probably
		 * interrupted (ctrl-c) us.
		 */
		if (signal_pending(current)) {
			rc = -ERESTARTSYS;
			break;
		}

		if (sleep_on_un_flags)
			old_flags = ch->ch_tun.un_flags | ch->ch_pun.un_flags;
		else
			old_flags = ch->ch_flags;

		/*
		 * Let go of channel lock before calling schedule.
		 * Our poller will get any FEP events and wake us up when DCD
		 * eventually goes active.
		 */

		spin_unlock_irqrestore(&ch->ch_lock, flags);

		/*
		 * Wait for something in the flags to change
		 * from the current value.
		 */
		if (sleep_on_un_flags)
			rc = wait_event_interruptible
				(un->un_flags_wait,
				 (old_flags != (ch->ch_tun.un_flags |
						ch->ch_pun.un_flags)));
		else
			rc = wait_event_interruptible(
					ch->ch_flags_wait,
					(old_flags != ch->ch_flags));

		/*
		 * We got woken up for some reason.
		 * Before looping around, grab our channel lock.
		 */
		spin_lock_irqsave(&ch->ch_lock, flags);
	}

	ch->ch_wopen--;

	spin_unlock_irqrestore(&ch->ch_lock, flags);

	return rc;
}