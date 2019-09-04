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
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ membase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ AML_UART_CONTROL ; 
 int AML_UART_RX_EMPTY ; 
 scalar_t__ AML_UART_STATUS ; 
 int AML_UART_TX_FULL ; 
 int AML_UART_TX_INT_EN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  meson_receive_chars (struct uart_port*) ; 
 int /*<<< orphan*/  meson_uart_start_tx (struct uart_port*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t meson_uart_interrupt(int irq, void *dev_id)
{
	struct uart_port *port = (struct uart_port *)dev_id;

	spin_lock(&port->lock);

	if (!(readl(port->membase + AML_UART_STATUS) & AML_UART_RX_EMPTY))
		meson_receive_chars(port);

	if (!(readl(port->membase + AML_UART_STATUS) & AML_UART_TX_FULL)) {
		if (readl(port->membase + AML_UART_CONTROL) & AML_UART_TX_INT_EN)
			meson_uart_start_tx(port);
	}

	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}