#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uart_port {int /*<<< orphan*/  lock; } ;
struct pic32_sport {int /*<<< orphan*/  irq_rx; int /*<<< orphan*/  irq_tx; int /*<<< orphan*/  irq_fault; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  pic32_disable_clock (struct pic32_sport*) ; 
 int /*<<< orphan*/  pic32_uart_dsbl_and_mask (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pic32_sport* to_pic32_sport (struct uart_port*) ; 

__attribute__((used)) static void pic32_uart_shutdown(struct uart_port *port)
{
	struct pic32_sport *sport = to_pic32_sport(port);
	unsigned long flags;

	/* disable uart */
	spin_lock_irqsave(&port->lock, flags);
	pic32_uart_dsbl_and_mask(port);
	spin_unlock_irqrestore(&port->lock, flags);
	pic32_disable_clock(sport);

	/* free all 3 interrupts for this UART */
	free_irq(sport->irq_fault, port);
	free_irq(sport->irq_tx, port);
	free_irq(sport->irq_rx, port);
}