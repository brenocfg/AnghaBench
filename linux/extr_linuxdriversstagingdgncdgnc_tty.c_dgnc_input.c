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
typedef  int ushort ;
typedef  int uint ;
struct tty_struct {int /*<<< orphan*/  port; } ;
struct tty_ldisc {TYPE_2__* ops; } ;
struct dgnc_board {int dummy; } ;
struct TYPE_3__ {int un_flags; struct tty_struct* un_tty; } ;
struct channel_t {int ch_r_head; int ch_r_tail; int ch_flags; unsigned char* ch_equeue; int ch_e_tail; int /*<<< orphan*/  ch_lock; TYPE_1__ ch_tun; struct dgnc_board* ch_bd; } ;
struct TYPE_4__ {int /*<<< orphan*/  receive_buf; } ;

/* Variables and functions */
 int CH_FORCED_STOPI ; 
 int /*<<< orphan*/  C_CREAD (struct tty_struct*) ; 
 scalar_t__ I_BRKINT (struct tty_struct*) ; 
 scalar_t__ I_INPCK (struct tty_struct*) ; 
 scalar_t__ I_PARMRK (struct tty_struct*) ; 
 int N_TTY_BUF_SIZE ; 
 int RQUEUEMASK ; 
 int RQUEUESIZE ; 
 char TTY_BREAK ; 
 int TTY_FLIPBUF_SIZE ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_PARITY ; 
 unsigned char UART_LSR_BI ; 
 unsigned char UART_LSR_FE ; 
 unsigned char UART_LSR_PE ; 
 int UN_CLOSING ; 
 int UN_ISOPEN ; 
 int /*<<< orphan*/  dgnc_check_queue_flow_control (struct channel_t*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tty_buffer_request_room (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ ,unsigned char,char) ; 
 int /*<<< orphan*/  tty_insert_flip_string (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 struct tty_ldisc* tty_ldisc_ref (struct tty_struct*) ; 

void dgnc_input(struct channel_t *ch)
{
	struct dgnc_board *bd;
	struct tty_struct *tp;
	struct tty_ldisc *ld = NULL;
	uint	rmask;
	ushort	head;
	ushort	tail;
	int	data_len;
	unsigned long flags;
	int flip_len;
	int len = 0;
	int n = 0;
	int s = 0;
	int i = 0;

	if (!ch)
		return;

	tp = ch->ch_tun.un_tty;

	bd = ch->ch_bd;
	if (!bd)
		return;

	spin_lock_irqsave(&ch->ch_lock, flags);

	rmask = RQUEUEMASK;
	head = ch->ch_r_head & rmask;
	tail = ch->ch_r_tail & rmask;
	data_len = (head - tail) & rmask;

	if (data_len == 0)
		goto exit_unlock;

	/*
	 * If the device is not open, or CREAD is off,
	 * flush input data and return immediately.
	 */
	if (!tp ||
	    !(ch->ch_tun.un_flags & UN_ISOPEN) ||
	    !C_CREAD(tp) ||
	    (ch->ch_tun.un_flags & UN_CLOSING)) {
		ch->ch_r_head = tail;

		/* Force queue flow control to be released, if needed */
		dgnc_check_queue_flow_control(ch);

		goto exit_unlock;
	}

	if (ch->ch_flags & CH_FORCED_STOPI)
		goto exit_unlock;

	flip_len = TTY_FLIPBUF_SIZE;

	len = min(data_len, flip_len);
	len = min(len, (N_TTY_BUF_SIZE - 1));

	ld = tty_ldisc_ref(tp);
	if (!ld) {
		len = 0;
	} else {
		if (!ld->ops->receive_buf) {
			ch->ch_r_head = ch->ch_r_tail;
			len = 0;
		}
	}

	if (len <= 0)
		goto exit_unlock;

	/*
	 * The tty layer in the kernel has changed in 2.6.16+.
	 *
	 * The flip buffers in the tty structure are no longer exposed,
	 * and probably will be going away eventually.
	 *
	 * If we are completely raw, we don't need to go through a lot
	 * of the tty layers that exist.
	 * In this case, we take the shortest and fastest route we
	 * can to relay the data to the user.
	 *
	 * On the other hand, if we are not raw, we need to go through
	 * the new 2.6.16+ tty layer, which has its API more well defined.
	 */
	len = tty_buffer_request_room(tp->port, len);
	n = len;

	/*
	 * n now contains the most amount of data we can copy,
	 * bounded either by how much the Linux tty layer can handle,
	 * or the amount of data the card actually has pending...
	 */
	while (n) {
		unsigned char *ch_pos = ch->ch_equeue + tail;

		s = ((head >= tail) ? head : RQUEUESIZE) - tail;
		s = min(s, n);

		if (s <= 0)
			break;

		/*
		 * If conditions are such that ld needs to see all
		 * UART errors, we will have to walk each character
		 * and error byte and send them to the buffer one at
		 * a time.
		 */
		if (I_PARMRK(tp) || I_BRKINT(tp) || I_INPCK(tp)) {
			for (i = 0; i < s; i++) {
				unsigned char ch = *(ch_pos + i);
				char flag = TTY_NORMAL;

				if (ch & UART_LSR_BI)
					flag = TTY_BREAK;
				else if (ch & UART_LSR_PE)
					flag = TTY_PARITY;
				else if (ch & UART_LSR_FE)
					flag = TTY_FRAME;

				tty_insert_flip_char(tp->port, ch, flag);
			}
		} else {
			tty_insert_flip_string(tp->port, ch_pos, s);
		}

		tail += s;
		n -= s;
		/* Flip queue if needed */
		tail &= rmask;
	}

	ch->ch_r_tail = tail & rmask;
	ch->ch_e_tail = tail & rmask;
	dgnc_check_queue_flow_control(ch);
	spin_unlock_irqrestore(&ch->ch_lock, flags);

	/* Tell the tty layer its okay to "eat" the data now */
	tty_flip_buffer_push(tp->port);

	if (ld)
		tty_ldisc_deref(ld);
	return;

exit_unlock:
	spin_unlock_irqrestore(&ch->ch_lock, flags);
	if (ld)
		tty_ldisc_deref(ld);
}