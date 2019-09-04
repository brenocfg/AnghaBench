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
struct stm32_port {scalar_t__ rx_ch; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_receive_chars (struct uart_port*,int) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 

__attribute__((used)) static irqreturn_t stm32_threaded_interrupt(int irq, void *ptr)
{
	struct uart_port *port = ptr;
	struct stm32_port *stm32_port = to_stm32_port(port);

	spin_lock(&port->lock);

	if (stm32_port->rx_ch)
		stm32_receive_chars(port, true);

	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}