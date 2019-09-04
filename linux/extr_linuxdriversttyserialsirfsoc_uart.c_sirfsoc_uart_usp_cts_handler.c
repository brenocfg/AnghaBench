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
struct sirfsoc_uart_port {int /*<<< orphan*/  cts_gpio; scalar_t__ ms_enabled; struct uart_port port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_handle_cts_change (struct uart_port*,int) ; 

__attribute__((used)) static irqreturn_t sirfsoc_uart_usp_cts_handler(int irq, void *dev_id)
{
	struct sirfsoc_uart_port *sirfport = (struct sirfsoc_uart_port *)dev_id;
	struct uart_port *port = &sirfport->port;
	spin_lock(&port->lock);
	if (gpio_is_valid(sirfport->cts_gpio) && sirfport->ms_enabled)
		uart_handle_cts_change(port,
				!gpio_get_value(sirfport->cts_gpio));
	spin_unlock(&port->lock);
	return IRQ_HANDLED;
}