#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
typedef  int u8 ;
struct jsm_channel {int ch_flags; TYPE_1__* ch_cls_uart; int /*<<< orphan*/  ch_lock; } ;
struct jsm_board {size_t nasync; struct jsm_channel** channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  msr; int /*<<< orphan*/  isr_fcr; } ;

/* Variables and functions */
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 int UART_IIR_NO_INT ; 
 int UART_IIR_RDI ; 
 int UART_IIR_RDI_TIMEOUT ; 
 int UART_IIR_THRI ; 
 int /*<<< orphan*/  cls_copy_data_from_queue_to_uart (struct jsm_channel*) ; 
 int /*<<< orphan*/  cls_copy_data_from_uart_to_queue (struct jsm_channel*) ; 
 int /*<<< orphan*/  cls_parse_modem (struct jsm_channel*,int) ; 
 int /*<<< orphan*/  jsm_check_queue_flow_control (struct jsm_channel*) ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void cls_parse_isr(struct jsm_board *brd, uint port)
{
	struct jsm_channel *ch;
	u8 isr = 0;
	unsigned long flags;

	/*
	 * No need to verify board pointer, it was already
	 * verified in the interrupt routine.
	 */

	if (port >= brd->nasync)
		return;

	ch = brd->channels[port];
	if (!ch)
		return;

	/* Here we try to figure out what caused the interrupt to happen */
	while (1) {
		isr = readb(&ch->ch_cls_uart->isr_fcr);

		/* Bail if no pending interrupt on port */
		if (isr & UART_IIR_NO_INT)
			break;

		/* Receive Interrupt pending */
		if (isr & (UART_IIR_RDI | UART_IIR_RDI_TIMEOUT)) {
			/* Read data from uart -> queue */
			cls_copy_data_from_uart_to_queue(ch);
			jsm_check_queue_flow_control(ch);
		}

		/* Transmit Hold register empty pending */
		if (isr & UART_IIR_THRI) {
			/* Transfer data (if any) from Write Queue -> UART. */
			spin_lock_irqsave(&ch->ch_lock, flags);
			ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
			spin_unlock_irqrestore(&ch->ch_lock, flags);
			cls_copy_data_from_queue_to_uart(ch);
		}

		/*
		 * CTS/RTS change of state:
		 * Don't need to do anything, the cls_parse_modem
		 * below will grab the updated modem signals.
		 */

		/* Parse any modem signal changes */
		cls_parse_modem(ch, readb(&ch->ch_cls_uart->msr));
	}
}