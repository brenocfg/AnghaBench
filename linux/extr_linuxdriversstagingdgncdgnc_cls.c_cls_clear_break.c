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
struct channel_t {int ch_flags; int /*<<< orphan*/  ch_lock; scalar_t__ ch_stop_sending_break; TYPE_1__* ch_cls_uart; } ;
struct TYPE_2__ {int /*<<< orphan*/  lcr; } ;

/* Variables and functions */
 int CH_BREAK_SENDING ; 
 unsigned char UART_LCR_SBC ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cls_clear_break(struct channel_t *ch, int force)
{
	unsigned long flags;

	if (!ch)
		return;

	spin_lock_irqsave(&ch->ch_lock, flags);

	if (!ch->ch_stop_sending_break) {
		spin_unlock_irqrestore(&ch->ch_lock, flags);
		return;
	}

	/* Turn break off, and unset some variables */
	if (ch->ch_flags & CH_BREAK_SENDING) {
		if (time_after(jiffies, ch->ch_stop_sending_break) || force) {
			unsigned char temp = readb(&ch->ch_cls_uart->lcr);

			writeb((temp & ~UART_LCR_SBC), &ch->ch_cls_uart->lcr);
			ch->ch_flags &= ~(CH_BREAK_SENDING);
			ch->ch_stop_sending_break = 0;
		}
	}
	spin_unlock_irqrestore(&ch->ch_lock, flags);
}