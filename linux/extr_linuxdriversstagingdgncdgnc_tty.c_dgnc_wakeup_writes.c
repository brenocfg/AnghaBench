#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int un_flags; int /*<<< orphan*/  un_flags_wait; int /*<<< orphan*/  un_tty; } ;
struct TYPE_7__ {int un_flags; int /*<<< orphan*/  un_flags_wait; int /*<<< orphan*/  un_tty; } ;
struct TYPE_6__ {int digi_flags; } ;
struct channel_t {int ch_w_head; int ch_w_tail; int /*<<< orphan*/  ch_lock; TYPE_5__ ch_pun; TYPE_4__* ch_bd; TYPE_2__ ch_tun; TYPE_1__ ch_digi; } ;
struct TYPE_9__ {TYPE_3__* bd_ops; } ;
struct TYPE_8__ {scalar_t__ (* get_uart_bytes_left ) (struct channel_t*) ;} ;

/* Variables and functions */
 int DIGI_DTR_TOGGLE ; 
 int DIGI_RTS_TOGGLE ; 
 int /*<<< orphan*/  UART_MCR_DTR ; 
 int /*<<< orphan*/  UART_MCR_RTS ; 
 int UN_EMPTY ; 
 int UN_ISOPEN ; 
 int WQUEUESIZE ; 
 int /*<<< orphan*/  dgnc_set_signal_low (struct channel_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (struct channel_t*) ; 
 scalar_t__ stub2 (struct channel_t*) ; 
 int /*<<< orphan*/  tty_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void dgnc_wakeup_writes(struct channel_t *ch)
{
	int qlen = 0;
	unsigned long flags;

	if (!ch)
		return;

	spin_lock_irqsave(&ch->ch_lock, flags);

	/* If channel now has space, wake up anyone waiting on the condition. */

	qlen = ch->ch_w_head - ch->ch_w_tail;
	if (qlen < 0)
		qlen += WQUEUESIZE;

	if (qlen >= (WQUEUESIZE - 256)) {
		spin_unlock_irqrestore(&ch->ch_lock, flags);
		return;
	}

	if (ch->ch_tun.un_flags & UN_ISOPEN) {
		tty_wakeup(ch->ch_tun.un_tty);

		/*
		 * If unit is set to wait until empty, check to make sure
		 * the queue AND FIFO are both empty.
		 */
		if (ch->ch_tun.un_flags & UN_EMPTY) {
			if ((qlen == 0) &&
			    (ch->ch_bd->bd_ops->get_uart_bytes_left(ch) == 0)) {
				ch->ch_tun.un_flags &= ~(UN_EMPTY);

				/*
				 * If RTS Toggle mode is on, whenever
				 * the queue and UART is empty, keep RTS low.
				 */
				if (ch->ch_digi.digi_flags & DIGI_RTS_TOGGLE)
					dgnc_set_signal_low(ch, UART_MCR_RTS);

				/*
				 * If DTR Toggle mode is on, whenever
				 * the queue and UART is empty, keep DTR low.
				 */
				if (ch->ch_digi.digi_flags & DIGI_DTR_TOGGLE)
					dgnc_set_signal_low(ch, UART_MCR_DTR);
			}
		}

		wake_up_interruptible(&ch->ch_tun.un_flags_wait);
	}

	if (ch->ch_pun.un_flags & UN_ISOPEN) {
		tty_wakeup(ch->ch_pun.un_tty);

		/*
		 * If unit is set to wait until empty, check to make sure
		 * the queue AND FIFO are both empty.
		 */
		if (ch->ch_pun.un_flags & UN_EMPTY) {
			if ((qlen == 0) &&
			    (ch->ch_bd->bd_ops->get_uart_bytes_left(ch) == 0))
				ch->ch_pun.un_flags &= ~(UN_EMPTY);
		}

		wake_up_interruptible(&ch->ch_pun.un_flags_wait);
	}

	spin_unlock_irqrestore(&ch->ch_lock, flags);
}