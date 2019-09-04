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
typedef  int ushort ;
typedef  scalar_t__ uint ;
struct TYPE_5__ {int /*<<< orphan*/  un_flags; } ;
struct TYPE_4__ {int digi_flags; } ;
struct channel_t {int ch_w_tail; int ch_w_head; int ch_flags; int ch_mostat; int /*<<< orphan*/  ch_lock; int /*<<< orphan*/  ch_txcount; TYPE_3__* ch_cls_uart; int /*<<< orphan*/ * ch_wqueue; TYPE_2__ ch_tun; TYPE_1__ ch_digi; } ;
struct TYPE_6__ {int /*<<< orphan*/  txrx; } ;

/* Variables and functions */
 int CH_BREAK_SENDING ; 
 int CH_FORCED_STOP ; 
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 int DIGI_DTR_TOGGLE ; 
 int DIGI_RTS_TOGGLE ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  UN_EMPTY ; 
 int WQUEUEMASK ; 
 int /*<<< orphan*/  cls_assert_modem_signals (struct channel_t*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_copy_data_from_queue_to_uart(struct channel_t *ch)
{
	ushort head;
	ushort tail;
	int n;
	int qlen;
	uint len_written = 0;
	unsigned long flags;

	if (!ch)
		return;

	spin_lock_irqsave(&ch->ch_lock, flags);

	if (ch->ch_w_tail == ch->ch_w_head)
		goto exit_unlock;

	/* If port is "stopped", don't send any data to the UART */
	if ((ch->ch_flags & CH_FORCED_STOP) ||
	    (ch->ch_flags & CH_BREAK_SENDING))
		goto exit_unlock;

	if (!(ch->ch_flags & (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM)))
		goto exit_unlock;

	n = 32;

	head = ch->ch_w_head & WQUEUEMASK;
	tail = ch->ch_w_tail & WQUEUEMASK;
	qlen = (head - tail) & WQUEUEMASK;

	n = min(n, qlen);

	while (n > 0) {
		/*
		 * If RTS Toggle mode is on, turn on RTS now if not already set,
		 * and make sure we get an event when the data transfer has
		 * completed.
		 */
		if (ch->ch_digi.digi_flags & DIGI_RTS_TOGGLE) {
			if (!(ch->ch_mostat & UART_MCR_RTS)) {
				ch->ch_mostat |= (UART_MCR_RTS);
				cls_assert_modem_signals(ch);
			}
			ch->ch_tun.un_flags |= (UN_EMPTY);
		}

		/*
		 * If DTR Toggle mode is on, turn on DTR now if not already set,
		 * and make sure we get an event when the data transfer has
		 * completed.
		 */
		if (ch->ch_digi.digi_flags & DIGI_DTR_TOGGLE) {
			if (!(ch->ch_mostat & UART_MCR_DTR)) {
				ch->ch_mostat |= (UART_MCR_DTR);
				cls_assert_modem_signals(ch);
			}
			ch->ch_tun.un_flags |= (UN_EMPTY);
		}
		writeb(ch->ch_wqueue[ch->ch_w_tail], &ch->ch_cls_uart->txrx);
		ch->ch_w_tail++;
		ch->ch_w_tail &= WQUEUEMASK;
		ch->ch_txcount++;
		len_written++;
		n--;
	}

	if (len_written > 0)
		ch->ch_flags &= ~(CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);

exit_unlock:
	spin_unlock_irqrestore(&ch->ch_lock, flags);
}