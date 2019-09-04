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
struct un_t {int un_flags; int /*<<< orphan*/  un_open_count; struct tty_struct* un_tty; int /*<<< orphan*/  un_type; } ;
struct TYPE_4__ {int /*<<< orphan*/ * c_cc; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; int /*<<< orphan*/  c_cflag; } ;
struct tty_struct {TYPE_1__ termios; struct un_t* driver_data; } ;
struct file {int dummy; } ;
struct dgnc_board {int state; size_t nasync; int /*<<< orphan*/  bd_lock; TYPE_3__* bd_ops; struct channel_t** channels; int /*<<< orphan*/  state_wait; } ;
struct TYPE_5__ {int digi_flags; } ;
struct channel_t {int ch_flags; int /*<<< orphan*/  ch_lock; int /*<<< orphan*/  ch_open_count; int /*<<< orphan*/  ch_mostat; TYPE_2__ ch_digi; int /*<<< orphan*/  ch_stopc; int /*<<< orphan*/  ch_startc; int /*<<< orphan*/  ch_c_lflag; int /*<<< orphan*/  ch_c_oflag; int /*<<< orphan*/  ch_c_iflag; int /*<<< orphan*/  ch_c_cflag; scalar_t__ ch_stops_sent; scalar_t__ ch_stop_sending_break; scalar_t__ ch_cached_lsr; scalar_t__ ch_w_tail; scalar_t__ ch_w_head; scalar_t__ ch_e_tail; scalar_t__ ch_e_head; scalar_t__ ch_r_tail; scalar_t__ ch_r_head; struct un_t ch_pun; struct un_t ch_tun; int /*<<< orphan*/  ch_flags_wait; void* ch_wqueue; void* ch_equeue; void* ch_rqueue; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* param ) (struct tty_struct*) ;int /*<<< orphan*/  (* uart_init ) (struct channel_t*) ;int /*<<< orphan*/  (* flush_uart_read ) (struct channel_t*) ;int /*<<< orphan*/  (* flush_uart_write ) (struct channel_t*) ;} ;

/* Variables and functions */
 int BOARD_READY ; 
 int CH_OPENING ; 
 int /*<<< orphan*/  DGNC_PRINT ; 
 int /*<<< orphan*/  DGNC_SERIAL ; 
 int DIGI_DTR_TOGGLE ; 
 int DIGI_RTS_TOGGLE ; 
 int EINTR ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  EQUEUESIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_PRINT (int) ; 
 int MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 size_t PORT_NUM (int) ; 
 int /*<<< orphan*/  RQUEUESIZE ; 
 int /*<<< orphan*/  UART_MCR_DTR ; 
 int /*<<< orphan*/  UART_MCR_RTS ; 
 int UN_CLOSING ; 
 int UN_ISOPEN ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  WQUEUESIZE ; 
 int dgnc_block_til_ready (struct tty_struct*,struct file*,struct channel_t*) ; 
 int /*<<< orphan*/  dgnc_carrier (struct channel_t*) ; 
 struct dgnc_board* find_board_by_major (int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct channel_t*) ; 
 int /*<<< orphan*/  stub2 (struct channel_t*) ; 
 int /*<<< orphan*/  stub3 (struct channel_t*) ; 
 int /*<<< orphan*/  stub4 (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_devnum (struct tty_struct*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dgnc_tty_open(struct tty_struct *tty, struct file *file)
{
	struct dgnc_board	*brd;
	struct channel_t *ch;
	struct un_t	*un;
	uint		major = 0;
	uint		minor = 0;
	int		rc = 0;
	unsigned long flags;

	rc = 0;

	major = MAJOR(tty_devnum(tty));
	minor = MINOR(tty_devnum(tty));

	if (major > 255)
		return -ENXIO;

	brd = find_board_by_major(major);
	if (!brd)
		return -ENXIO;

	rc = wait_event_interruptible(brd->state_wait,
				      (brd->state & BOARD_READY));
	if (rc)
		return rc;

	spin_lock_irqsave(&brd->bd_lock, flags);

	if (PORT_NUM(minor) >= brd->nasync) {
		rc = -ENXIO;
		goto err_brd_unlock;
	}

	ch = brd->channels[PORT_NUM(minor)];
	if (!ch) {
		rc = -ENXIO;
		goto err_brd_unlock;
	}

	spin_unlock_irqrestore(&brd->bd_lock, flags);

	spin_lock_irqsave(&ch->ch_lock, flags);

	/* Figure out our type */
	if (!IS_PRINT(minor)) {
		un = &brd->channels[PORT_NUM(minor)]->ch_tun;
		un->un_type = DGNC_SERIAL;
	} else if (IS_PRINT(minor)) {
		un = &brd->channels[PORT_NUM(minor)]->ch_pun;
		un->un_type = DGNC_PRINT;
	} else {
		rc = -ENXIO;
		goto err_ch_unlock;
	}

	/*
	 * If the port is still in a previous open, and in a state
	 * where we simply cannot safely keep going, wait until the
	 * state clears.
	 */
	spin_unlock_irqrestore(&ch->ch_lock, flags);

	rc = wait_event_interruptible(ch->ch_flags_wait,
				      ((ch->ch_flags & CH_OPENING) == 0));
	/* If ret is non-zero, user ctrl-c'ed us */
	if (rc)
		return -EINTR;

	/*
	 * If either unit is in the middle of the fragile part of close,
	 * we just cannot touch the channel safely.
	 * Go to sleep, knowing that when the channel can be
	 * touched safely, the close routine will signal the
	 * ch_flags_wait to wake us back up.
	 */
	rc = wait_event_interruptible(ch->ch_flags_wait,
				      !((ch->ch_tun.un_flags |
				      ch->ch_pun.un_flags) & UN_CLOSING));
	/* If ret is non-zero, user ctrl-c'ed us */
	if (rc)
		return -EINTR;

	spin_lock_irqsave(&ch->ch_lock, flags);

	tty->driver_data = un;

	/* Initialize tty's */

	if (!(un->un_flags & UN_ISOPEN)) {
		un->un_tty = tty;

		/* Maybe do something here to the TTY struct as well? */
	}

	/*
	 * Allocate channel buffers for read/write/error.
	 * Set flag, so we don't get trounced on.
	 */
	ch->ch_flags |= (CH_OPENING);

	spin_unlock_irqrestore(&ch->ch_lock, flags);

	if (!ch->ch_rqueue)
		ch->ch_rqueue = kzalloc(RQUEUESIZE, GFP_KERNEL);
	if (!ch->ch_equeue)
		ch->ch_equeue = kzalloc(EQUEUESIZE, GFP_KERNEL);
	if (!ch->ch_wqueue)
		ch->ch_wqueue = kzalloc(WQUEUESIZE, GFP_KERNEL);

	if (!ch->ch_rqueue || !ch->ch_equeue || !ch->ch_wqueue) {
		kfree(ch->ch_rqueue);
		kfree(ch->ch_equeue);
		kfree(ch->ch_wqueue);
		return -ENOMEM;
	}

	spin_lock_irqsave(&ch->ch_lock, flags);

	ch->ch_flags &= ~(CH_OPENING);
	wake_up_interruptible(&ch->ch_flags_wait);

	/* Initialize if neither terminal or printer is open. */

	if (!((ch->ch_tun.un_flags | ch->ch_pun.un_flags) & UN_ISOPEN)) {
		/* Flush input queues. */
		ch->ch_r_head = 0;
		ch->ch_r_tail = 0;
		ch->ch_e_head = 0;
		ch->ch_e_tail = 0;
		ch->ch_w_head = 0;
		ch->ch_w_tail = 0;

		brd->bd_ops->flush_uart_write(ch);
		brd->bd_ops->flush_uart_read(ch);

		ch->ch_flags = 0;
		ch->ch_cached_lsr = 0;
		ch->ch_stop_sending_break = 0;
		ch->ch_stops_sent = 0;

		ch->ch_c_cflag   = tty->termios.c_cflag;
		ch->ch_c_iflag   = tty->termios.c_iflag;
		ch->ch_c_oflag   = tty->termios.c_oflag;
		ch->ch_c_lflag   = tty->termios.c_lflag;
		ch->ch_startc = tty->termios.c_cc[VSTART];
		ch->ch_stopc  = tty->termios.c_cc[VSTOP];

		/*
		 * Bring up RTS and DTR...
		 * Also handle RTS or DTR toggle if set.
		 */
		if (!(ch->ch_digi.digi_flags & DIGI_RTS_TOGGLE))
			ch->ch_mostat |= (UART_MCR_RTS);
		if (!(ch->ch_digi.digi_flags & DIGI_DTR_TOGGLE))
			ch->ch_mostat |= (UART_MCR_DTR);

		/* Tell UART to init itself */
		brd->bd_ops->uart_init(ch);
	}

	brd->bd_ops->param(tty);

	dgnc_carrier(ch);

	spin_unlock_irqrestore(&ch->ch_lock, flags);

	rc = dgnc_block_til_ready(tty, file, ch);

	spin_lock_irqsave(&ch->ch_lock, flags);
	ch->ch_open_count++;
	un->un_open_count++;
	un->un_flags |= (UN_ISOPEN);
	spin_unlock_irqrestore(&ch->ch_lock, flags);

	return rc;

err_brd_unlock:
	spin_unlock_irqrestore(&brd->bd_lock, flags);

	return rc;
err_ch_unlock:
	spin_unlock_irqrestore(&ch->ch_lock, flags);

	return rc;
}