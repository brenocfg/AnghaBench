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
struct uart_port {TYPE_1__* state; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ULITE_STATUS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int uart_in32 (int /*<<< orphan*/ ,struct uart_port*) ; 
 int ulite_receive (struct uart_port*,int) ; 
 int ulite_transmit (struct uart_port*,int) ; 

__attribute__((used)) static irqreturn_t ulite_isr(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	int stat, busy, n = 0;
	unsigned long flags;

	do {
		spin_lock_irqsave(&port->lock, flags);
		stat = uart_in32(ULITE_STATUS, port);
		busy  = ulite_receive(port, stat);
		busy |= ulite_transmit(port, stat);
		spin_unlock_irqrestore(&port->lock, flags);
		n++;
	} while (busy);

	/* work done? */
	if (n > 1) {
		tty_flip_buffer_push(&port->state->port);
		return IRQ_HANDLED;
	} else {
		return IRQ_NONE;
	}
}