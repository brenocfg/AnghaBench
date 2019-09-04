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
struct dgnc_board {size_t nasync; struct channel_t** channels; } ;
struct channel_t {int ch_flags; TYPE_1__* ch_cls_uart; int /*<<< orphan*/  ch_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  msr; int /*<<< orphan*/  isr_fcr; } ;

/* Variables and functions */
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 unsigned char UART_IIR_NO_INT ; 
 unsigned char UART_IIR_RDI ; 
 unsigned char UART_IIR_RDI_TIMEOUT ; 
 unsigned char UART_IIR_THRI ; 
 int /*<<< orphan*/  cls_copy_data_from_queue_to_uart (struct channel_t*) ; 
 int /*<<< orphan*/  cls_copy_data_from_uart_to_queue (struct channel_t*) ; 
 int /*<<< orphan*/  cls_parse_modem (struct channel_t*,unsigned char) ; 
 int /*<<< orphan*/  dgnc_check_queue_flow_control (struct channel_t*) ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void cls_parse_isr(struct dgnc_board *brd, uint port)
{
	struct channel_t *ch;
	unsigned char isr = 0;
	unsigned long flags;

	/*
	 * No need to verify board pointer, it was already
	 * verified in the interrupt routine.
	 */

	if (port >= brd->nasync)
		return;

	ch = brd->channels[port];

	/* Here we try to figure out what caused the interrupt to happen */
	while (1) {
		isr = readb(&ch->ch_cls_uart->isr_fcr);

		if (isr & UART_IIR_NO_INT)
			break;

		/* Receive Interrupt pending */
		if (isr & (UART_IIR_RDI | UART_IIR_RDI_TIMEOUT)) {
			cls_copy_data_from_uart_to_queue(ch);
			dgnc_check_queue_flow_control(ch);
		}

		/* Transmit Hold register empty pending */
		if (isr & UART_IIR_THRI) {
			spin_lock_irqsave(&ch->ch_lock, flags);
			ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
			spin_unlock_irqrestore(&ch->ch_lock, flags);
			cls_copy_data_from_queue_to_uart(ch);
		}

		cls_parse_modem(ch, readb(&ch->ch_cls_uart->msr));
	}
}