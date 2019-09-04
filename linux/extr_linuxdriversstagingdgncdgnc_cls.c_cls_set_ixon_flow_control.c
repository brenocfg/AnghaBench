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
struct channel_t {unsigned char ch_startc; unsigned char ch_stopc; TYPE_1__* ch_cls_uart; } ;
struct TYPE_2__ {int /*<<< orphan*/  isr_fcr; int /*<<< orphan*/  ier; int /*<<< orphan*/  lcr; int /*<<< orphan*/  spr; int /*<<< orphan*/  msr; int /*<<< orphan*/  lsr; int /*<<< orphan*/  mcr; } ;

/* Variables and functions */
 unsigned char UART_16654_FCR_RXTRIGGER_16 ; 
 unsigned char UART_16654_FCR_TXTRIGGER_16 ; 
 unsigned char UART_EXAR654_EFR_CTSDSR ; 
 unsigned char UART_EXAR654_EFR_ECB ; 
 unsigned char UART_EXAR654_EFR_IXON ; 
 unsigned char UART_EXAR654_ENHANCED_REGISTER_SET ; 
 unsigned char UART_EXAR654_IER_CTSDSR ; 
 unsigned char UART_EXAR654_IER_XOFF ; 
 unsigned char UART_FCR_CLEAR_RCVR ; 
 unsigned char UART_FCR_ENABLE_FIFO ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cls_set_ixon_flow_control(struct channel_t *ch)
{
	unsigned char lcrb = readb(&ch->ch_cls_uart->lcr);
	unsigned char ier = readb(&ch->ch_cls_uart->ier);
	unsigned char isr_fcr = 0;

	/*
	 * The Enhanced Register Set may only be accessed when
	 * the Line Control Register is set to 0xBFh.
	 */
	writeb(UART_EXAR654_ENHANCED_REGISTER_SET, &ch->ch_cls_uart->lcr);

	isr_fcr = readb(&ch->ch_cls_uart->isr_fcr);

	/* Turn on IXON flow control, turn off CTS flow control */
	isr_fcr |= (UART_EXAR654_EFR_ECB | UART_EXAR654_EFR_IXON);
	isr_fcr &= ~(UART_EXAR654_EFR_CTSDSR);

	writeb(isr_fcr, &ch->ch_cls_uart->isr_fcr);

	/* Now set our current start/stop chars while in enhanced mode */
	writeb(ch->ch_startc, &ch->ch_cls_uart->mcr);
	writeb(0, &ch->ch_cls_uart->lsr);
	writeb(ch->ch_stopc, &ch->ch_cls_uart->msr);
	writeb(0, &ch->ch_cls_uart->spr);

	/* Write old LCR value back out, which turns enhanced access off */
	writeb(lcrb, &ch->ch_cls_uart->lcr);

	/*
	 * Disable interrupts for CTS flow, turn on interrupts for
	 * received XOFF chars
	 */
	ier &= ~(UART_EXAR654_IER_CTSDSR);
	ier |= (UART_EXAR654_IER_XOFF);
	writeb(ier, &ch->ch_cls_uart->ier);

	/* Set the usual FIFO values */
	writeb((UART_FCR_ENABLE_FIFO), &ch->ch_cls_uart->isr_fcr);

	writeb((UART_FCR_ENABLE_FIFO | UART_16654_FCR_RXTRIGGER_16 |
		UART_16654_FCR_TXTRIGGER_16 | UART_FCR_CLEAR_RCVR),
		&ch->ch_cls_uart->isr_fcr);
}