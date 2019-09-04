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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int RXIENB ; 
 unsigned int TXEMPTY ; 
 unsigned int TXIENB ; 
 unsigned int UART_GET_STATUS (struct uart_port*) ; 
 int /*<<< orphan*/  UART_TX_IRQ_DISABLE (struct uart_port*) ; 
 int /*<<< orphan*/  arc_serial_rx_chars (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  arc_serial_tx_chars (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_tx_stopped (struct uart_port*) ; 

__attribute__((used)) static irqreturn_t arc_serial_isr(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	unsigned int status;

	status = UART_GET_STATUS(port);

	/*
	 * Single IRQ for both Rx (data available) Tx (room available) Interrupt
	 * notifications from the UART Controller.
	 * To demultiplex between the two, we check the relevant bits
	 */
	if (status & RXIENB) {

		/* already in ISR, no need of xx_irqsave */
		spin_lock(&port->lock);
		arc_serial_rx_chars(port, status);
		spin_unlock(&port->lock);
	}

	if ((status & TXIENB) && (status & TXEMPTY)) {

		/* Unconditionally disable further Tx-Interrupts.
		 * will be enabled by tx_chars() if needed.
		 */
		UART_TX_IRQ_DISABLE(port);

		spin_lock(&port->lock);

		if (!uart_tx_stopped(port))
			arc_serial_tx_chars(port);

		spin_unlock(&port->lock);
	}

	return IRQ_HANDLED;
}