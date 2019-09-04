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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  spinlock; scalar_t__ port_tts; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_buff_add ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ UART_LSR ; 
 int UART_LSR_DR ; 
 scalar_t__ UART_RX ; 
 int inb_p (scalar_t__) ; 
 TYPE_2__ speakup_info ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* synth ; 

__attribute__((used)) static irqreturn_t synth_readbuf_handler(int irq, void *dev_id)
{
	unsigned long flags;
	int c;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	while (inb_p(speakup_info.port_tts + UART_LSR) & UART_LSR_DR) {
		c = inb_p(speakup_info.port_tts + UART_RX);
		synth->read_buff_add((u_char)c);
	}
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	return IRQ_HANDLED;
}