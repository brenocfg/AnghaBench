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
 unsigned int UART_GET_STATUS (struct uart_port*) ; 
 unsigned int UART_STATUS_DR ; 
 unsigned int UART_STATUS_THE ; 
 int /*<<< orphan*/  apbuart_rx_chars (struct uart_port*) ; 
 int /*<<< orphan*/  apbuart_tx_chars (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t apbuart_int(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	unsigned int status;

	spin_lock(&port->lock);

	status = UART_GET_STATUS(port);
	if (status & UART_STATUS_DR)
		apbuart_rx_chars(port);
	if (status & UART_STATUS_THE)
		apbuart_tx_chars(port);

	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}