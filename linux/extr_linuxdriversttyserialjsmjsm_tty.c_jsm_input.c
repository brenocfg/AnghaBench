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
typedef  int u32 ;
typedef  int u16 ;
struct tty_struct {int dummy; } ;
struct tty_port {struct tty_struct* tty; } ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct jsm_channel {int ch_r_head; int ch_r_tail; int ch_flags; int* ch_equeue; int ch_e_tail; struct jsm_board* ch_bd; int /*<<< orphan*/  ch_lock; int /*<<< orphan*/ * ch_rqueue; int /*<<< orphan*/  ch_portnum; TYPE_2__ uart_port; } ;
struct jsm_board {int /*<<< orphan*/  pci_dev; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 int CH_STOPI ; 
 int /*<<< orphan*/  C_CREAD (struct tty_struct*) ; 
 int /*<<< orphan*/  IOCTL ; 
 scalar_t__ I_BRKINT (struct tty_struct*) ; 
 scalar_t__ I_INPCK (struct tty_struct*) ; 
 scalar_t__ I_PARMRK (struct tty_struct*) ; 
 int /*<<< orphan*/  READ ; 
 int RQUEUEMASK ; 
 int RQUEUESIZE ; 
 int /*<<< orphan*/  TTY_BREAK ; 
 int /*<<< orphan*/  TTY_FRAME ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  TTY_PARITY ; 
 int UART_LSR_BI ; 
 int UART_LSR_FE ; 
 int UART_LSR_PE ; 
 int /*<<< orphan*/  jsm_check_queue_flow_control (struct jsm_channel*) ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tty_buffer_request_room (struct tty_port*,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_port*,int /*<<< orphan*/ *,int) ; 

void jsm_input(struct jsm_channel *ch)
{
	struct jsm_board *bd;
	struct tty_struct *tp;
	struct tty_port *port;
	u32 rmask;
	u16 head;
	u16 tail;
	int data_len;
	unsigned long lock_flags;
	int len = 0;
	int s = 0;
	int i = 0;

	jsm_dbg(READ, &ch->ch_bd->pci_dev, "start\n");

	port = &ch->uart_port.state->port;
	tp = port->tty;

	bd = ch->ch_bd;
	if (!bd)
		return;

	spin_lock_irqsave(&ch->ch_lock, lock_flags);

	/*
	 *Figure the number of characters in the buffer.
	 *Exit immediately if none.
	 */

	rmask = RQUEUEMASK;

	head = ch->ch_r_head & rmask;
	tail = ch->ch_r_tail & rmask;

	data_len = (head - tail) & rmask;
	if (data_len == 0) {
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		return;
	}

	jsm_dbg(READ, &ch->ch_bd->pci_dev, "start\n");

	/*
	 *If the device is not open, or CREAD is off, flush
	 *input data and return immediately.
	 */
	if (!tp || !C_CREAD(tp)) {

		jsm_dbg(READ, &ch->ch_bd->pci_dev,
			"input. dropping %d bytes on port %d...\n",
			data_len, ch->ch_portnum);
		ch->ch_r_head = tail;

		/* Force queue flow control to be released, if needed */
		jsm_check_queue_flow_control(ch);

		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		return;
	}

	/*
	 * If we are throttled, simply don't read any data.
	 */
	if (ch->ch_flags & CH_STOPI) {
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		jsm_dbg(READ, &ch->ch_bd->pci_dev,
			"Port %d throttled, not reading any data. head: %x tail: %x\n",
			ch->ch_portnum, head, tail);
		return;
	}

	jsm_dbg(READ, &ch->ch_bd->pci_dev, "start 2\n");

	len = tty_buffer_request_room(port, data_len);

	/*
	 * len now contains the most amount of data we can copy,
	 * bounded either by the flip buffer size or the amount
	 * of data the card actually has pending...
	 */
	while (len) {
		s = ((head >= tail) ? head : RQUEUESIZE) - tail;
		s = min(s, len);

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
				/*
				 * Give the Linux ld the flags in the
				 * format it likes.
				 */
				if (*(ch->ch_equeue +tail +i) & UART_LSR_BI)
					tty_insert_flip_char(port, *(ch->ch_rqueue +tail +i),  TTY_BREAK);
				else if (*(ch->ch_equeue +tail +i) & UART_LSR_PE)
					tty_insert_flip_char(port, *(ch->ch_rqueue +tail +i), TTY_PARITY);
				else if (*(ch->ch_equeue +tail +i) & UART_LSR_FE)
					tty_insert_flip_char(port, *(ch->ch_rqueue +tail +i), TTY_FRAME);
				else
					tty_insert_flip_char(port, *(ch->ch_rqueue +tail +i), TTY_NORMAL);
			}
		} else {
			tty_insert_flip_string(port, ch->ch_rqueue + tail, s);
		}
		tail += s;
		len -= s;
		/* Flip queue if needed */
		tail &= rmask;
	}

	ch->ch_r_tail = tail & rmask;
	ch->ch_e_tail = tail & rmask;
	jsm_check_queue_flow_control(ch);
	spin_unlock_irqrestore(&ch->ch_lock, lock_flags);

	/* Tell the tty layer its okay to "eat" the data now */
	tty_flip_buffer_push(port);

	jsm_dbg(IOCTL, &ch->ch_bd->pci_dev, "finish\n");
}