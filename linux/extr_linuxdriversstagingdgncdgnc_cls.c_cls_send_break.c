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
struct channel_t {int ch_flags; TYPE_1__* ch_cls_uart; scalar_t__ ch_stop_sending_break; } ;
struct TYPE_2__ {int /*<<< orphan*/  lcr; } ;

/* Variables and functions */
 int CH_BREAK_SENDING ; 
 unsigned char UART_LCR_SBC ; 
 scalar_t__ dgnc_jiffies_from_ms (int) ; 
 scalar_t__ jiffies ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_send_break(struct channel_t *ch, int msecs)
{
	if (!ch)
		return;

	/* If we receive a time of 0, this means turn off the break. */
	if (msecs == 0) {
		if (ch->ch_flags & CH_BREAK_SENDING) {
			unsigned char temp = readb(&ch->ch_cls_uart->lcr);

			writeb((temp & ~UART_LCR_SBC), &ch->ch_cls_uart->lcr);
			ch->ch_flags &= ~(CH_BREAK_SENDING);
			ch->ch_stop_sending_break = 0;
		}
		return;
	}

	/*
	 * Set the time we should stop sending the break.
	 * If we are already sending a break, toss away the existing
	 * time to stop, and use this new value instead.
	 */
	ch->ch_stop_sending_break = jiffies + dgnc_jiffies_from_ms(msecs);

	/* Tell the UART to start sending the break */
	if (!(ch->ch_flags & CH_BREAK_SENDING)) {
		unsigned char temp = readb(&ch->ch_cls_uart->lcr);

		writeb((temp | UART_LCR_SBC), &ch->ch_cls_uart->lcr);
		ch->ch_flags |= (CH_BREAK_SENDING);
	}
}