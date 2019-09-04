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
struct s3c24xx_uart_port {struct uart_port port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  s3c24xx_serial_rx_drain_fifo (struct s3c24xx_uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t s3c24xx_serial_rx_chars_pio(void *dev_id)
{
	struct s3c24xx_uart_port *ourport = dev_id;
	struct uart_port *port = &ourport->port;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	s3c24xx_serial_rx_drain_fifo(ourport);
	spin_unlock_irqrestore(&port->lock, flags);

	return IRQ_HANDLED;
}