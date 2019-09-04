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
typedef  int ushort ;
struct channel_t {int ch_r_head; int ch_r_tail; int ch_c_iflag; unsigned char* ch_equeue; int ch_e_head; int /*<<< orphan*/  ch_lock; int /*<<< orphan*/  ch_rxcount; int /*<<< orphan*/  ch_err_frame; int /*<<< orphan*/  ch_err_break; int /*<<< orphan*/  ch_err_parity; TYPE_1__* ch_cls_uart; void** ch_rqueue; int /*<<< orphan*/  ch_err_overrun; } ;
struct TYPE_2__ {int /*<<< orphan*/  txrx; int /*<<< orphan*/  lsr; } ;

/* Variables and functions */
 int EQUEUEMASK ; 
 int IGNBRK ; 
 int RQUEUEMASK ; 
 unsigned char UART_LSR_BI ; 
 unsigned char UART_LSR_DR ; 
 unsigned char UART_LSR_FE ; 
 unsigned char UART_LSR_PE ; 
 void* readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cls_copy_data_from_uart_to_queue(struct channel_t *ch)
{
	int qleft = 0;
	unsigned char linestatus = 0;
	unsigned char error_mask = 0;
	ushort head;
	ushort tail;
	unsigned long flags;

	if (!ch)
		return;

	spin_lock_irqsave(&ch->ch_lock, flags);

	head = ch->ch_r_head;
	tail = ch->ch_r_tail;

	qleft = tail - head - 1;
	if (qleft < 0)
		qleft += RQUEUEMASK + 1;

	/*
	 * Create a mask to determine whether we should
	 * insert the character (if any) into our queue.
	 */
	if (ch->ch_c_iflag & IGNBRK)
		error_mask |= UART_LSR_BI;

	while (1) {
		linestatus = readb(&ch->ch_cls_uart->lsr);

		if (!(linestatus & (UART_LSR_DR)))
			break;

		/* Discard character if we are ignoring the error mask. */
		if (linestatus & error_mask)  {
			linestatus = 0;
			readb(&ch->ch_cls_uart->txrx);
			continue;
		}

		/*
		 * If our queue is full, we have no choice but to drop some
		 * data. The assumption is that HWFLOW or SWFLOW should have
		 * stopped things way way before we got to this point.
		 */
		while (qleft < 1) {
			tail = (tail + 1) & RQUEUEMASK;
			ch->ch_r_tail = tail;
			ch->ch_err_overrun++;
			qleft++;
		}

		ch->ch_equeue[head] = linestatus & (UART_LSR_BI | UART_LSR_PE
								 | UART_LSR_FE);
		ch->ch_rqueue[head] = readb(&ch->ch_cls_uart->txrx);

		qleft--;

		if (ch->ch_equeue[head] & UART_LSR_PE)
			ch->ch_err_parity++;
		if (ch->ch_equeue[head] & UART_LSR_BI)
			ch->ch_err_break++;
		if (ch->ch_equeue[head] & UART_LSR_FE)
			ch->ch_err_frame++;

		head = (head + 1) & RQUEUEMASK;
		ch->ch_rxcount++;
	}

	ch->ch_r_head = head & RQUEUEMASK;
	ch->ch_e_head = head & EQUEUEMASK;

	spin_unlock_irqrestore(&ch->ch_lock, flags);
}