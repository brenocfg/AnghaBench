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
struct TYPE_2__ {int digi_flags; } ;
struct channel_t {unsigned char ch_mistat; int /*<<< orphan*/  ch_lock; TYPE_1__ ch_digi; } ;

/* Variables and functions */
 int DIGI_ALTPIN ; 
 unsigned char UART_MSR_CTS ; 
 unsigned char UART_MSR_DCD ; 
 unsigned char UART_MSR_DDCD ; 
 unsigned char UART_MSR_DDSR ; 
 unsigned char UART_MSR_DSR ; 
 unsigned char UART_MSR_RI ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cls_parse_modem(struct channel_t *ch, unsigned char signals)
{
	unsigned char msignals = signals;
	unsigned long flags;

	if (!ch)
		return;

	/*
	 * Do altpin switching. Altpin switches DCD and DSR.
	 * This prolly breaks DSRPACE, so we should be more clever here.
	 */
	spin_lock_irqsave(&ch->ch_lock, flags);
	if (ch->ch_digi.digi_flags & DIGI_ALTPIN) {
		unsigned char mswap = signals;

		if (mswap & UART_MSR_DDCD) {
			msignals &= ~UART_MSR_DDCD;
			msignals |= UART_MSR_DDSR;
		}
		if (mswap & UART_MSR_DDSR) {
			msignals &= ~UART_MSR_DDSR;
			msignals |= UART_MSR_DDCD;
		}
		if (mswap & UART_MSR_DCD) {
			msignals &= ~UART_MSR_DCD;
			msignals |= UART_MSR_DSR;
		}
		if (mswap & UART_MSR_DSR) {
			msignals &= ~UART_MSR_DSR;
			msignals |= UART_MSR_DCD;
		}
	}
	spin_unlock_irqrestore(&ch->ch_lock, flags);

	/* Scrub off lower bits. They signify delta's */
	signals &= 0xf0;

	spin_lock_irqsave(&ch->ch_lock, flags);
	if (msignals & UART_MSR_DCD)
		ch->ch_mistat |= UART_MSR_DCD;
	else
		ch->ch_mistat &= ~UART_MSR_DCD;

	if (msignals & UART_MSR_DSR)
		ch->ch_mistat |= UART_MSR_DSR;
	else
		ch->ch_mistat &= ~UART_MSR_DSR;

	if (msignals & UART_MSR_RI)
		ch->ch_mistat |= UART_MSR_RI;
	else
		ch->ch_mistat &= ~UART_MSR_RI;

	if (msignals & UART_MSR_CTS)
		ch->ch_mistat |= UART_MSR_CTS;
	else
		ch->ch_mistat &= ~UART_MSR_CTS;
	spin_unlock_irqrestore(&ch->ch_lock, flags);
}