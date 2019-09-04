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
struct un_t {int un_open_count; int un_flags; scalar_t__ un_type; int /*<<< orphan*/  un_flags_wait; int /*<<< orphan*/ * un_tty; struct channel_t* un_ch; } ;
struct tty_struct {int count; int closing; int /*<<< orphan*/  dev; struct un_t* driver_data; } ;
struct file {int dummy; } ;
struct dgnc_board {TYPE_1__* bd_ops; } ;
struct TYPE_4__ {int digi_flags; scalar_t__ digi_offlen; int /*<<< orphan*/  digi_offstr; } ;
struct channel_t {scalar_t__ ch_open_count; int ch_flags; int ch_c_cflag; int ch_mostat; int /*<<< orphan*/  ch_lock; int /*<<< orphan*/  ch_flags_wait; TYPE_2__ ch_digi; struct dgnc_board* ch_bd; scalar_t__ ch_old_baud; scalar_t__ ch_close_delay; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* uart_off ) (struct channel_t*) ;int /*<<< orphan*/  (* assert_modem_signals ) (struct channel_t*) ;int /*<<< orphan*/  (* drain ) (struct tty_struct*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CH_FORCED_STOPI ; 
 int CH_PRON ; 
 int CH_STOPI ; 
 scalar_t__ DGNC_PRINT ; 
 int DIGI_PRINTER ; 
 int HUPCL ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int UN_CLOSING ; 
 int UN_ISOPEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dgnc_tty_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  dgnc_wmove (struct channel_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep_interruptible (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct channel_t*) ; 
 int /*<<< orphan*/  stub3 (struct channel_t*) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dgnc_tty_close(struct tty_struct *tty, struct file *file)
{
	struct dgnc_board *bd;
	struct channel_t *ch;
	struct un_t *un;
	unsigned long flags;

	if (!tty)
		return;

	un = tty->driver_data;
	if (!un)
		return;

	ch = un->un_ch;
	if (!ch)
		return;

	bd = ch->ch_bd;
	if (!bd)
		return;

	spin_lock_irqsave(&ch->ch_lock, flags);

	/*
	 * Determine if this is the last close or not - and if we agree about
	 * which type of close it is with the Line Discipline
	 */
	if ((tty->count == 1) && (un->un_open_count != 1)) {
		/*
		 * Uh, oh.  tty->count is 1, which means that the tty
		 * structure will be freed.  un_open_count should always
		 * be one in these conditions.  If it's greater than
		 * one, we've got real problems, since it means the
		 * serial port won't be shutdown.
		 */
		dev_dbg(tty->dev,
			"tty->count is 1, un open count is %d\n",
			un->un_open_count);
		un->un_open_count = 1;
	}

	if (un->un_open_count)
		un->un_open_count--;
	else
		dev_dbg(tty->dev,
			"bad serial port open count of %d\n",
			un->un_open_count);

	ch->ch_open_count--;

	if (ch->ch_open_count && un->un_open_count) {
		spin_unlock_irqrestore(&ch->ch_lock, flags);
		return;
	}

	/* OK, its the last close on the unit */
	un->un_flags |= UN_CLOSING;

	tty->closing = 1;

	/*
	 * Only officially close channel if count is 0 and
	 * DIGI_PRINTER bit is not set.
	 */
	if ((ch->ch_open_count == 0) &&
	    !(ch->ch_digi.digi_flags & DIGI_PRINTER)) {
		ch->ch_flags &= ~(CH_STOPI | CH_FORCED_STOPI);

		/* turn off print device when closing print device. */

		if ((un->un_type == DGNC_PRINT) && (ch->ch_flags & CH_PRON)) {
			dgnc_wmove(ch, ch->ch_digi.digi_offstr,
				   (int)ch->ch_digi.digi_offlen);
			ch->ch_flags &= ~CH_PRON;
		}

		spin_unlock_irqrestore(&ch->ch_lock, flags);
		/* wait for output to drain */
		/* This will also return if we take an interrupt */

		bd->bd_ops->drain(tty, 0);

		dgnc_tty_flush_buffer(tty);
		tty_ldisc_flush(tty);

		spin_lock_irqsave(&ch->ch_lock, flags);

		tty->closing = 0;

		/* If we have HUPCL set, lower DTR and RTS */

		if (ch->ch_c_cflag & HUPCL) {
			/* Drop RTS/DTR */
			ch->ch_mostat &= ~(UART_MCR_DTR | UART_MCR_RTS);
			bd->bd_ops->assert_modem_signals(ch);

			/*
			 * Go to sleep to ensure RTS/DTR
			 * have been dropped for modems to see it.
			 */
			if (ch->ch_close_delay) {
				spin_unlock_irqrestore(&ch->ch_lock,
						       flags);
				msleep_interruptible(ch->ch_close_delay);
				spin_lock_irqsave(&ch->ch_lock, flags);
			}
		}

		ch->ch_old_baud = 0;

		/* Turn off UART interrupts for this port */
		ch->ch_bd->bd_ops->uart_off(ch);
	} else {
		/* turn off print device when closing print device. */

		if ((un->un_type == DGNC_PRINT) && (ch->ch_flags & CH_PRON)) {
			dgnc_wmove(ch, ch->ch_digi.digi_offstr,
				   (int)ch->ch_digi.digi_offlen);
			ch->ch_flags &= ~CH_PRON;
		}
	}

	un->un_tty = NULL;
	un->un_flags &= ~(UN_ISOPEN | UN_CLOSING);

	wake_up_interruptible(&ch->ch_flags_wait);
	wake_up_interruptible(&un->un_flags_wait);

	spin_unlock_irqrestore(&ch->ch_lock, flags);
}