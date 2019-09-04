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
struct uart_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  UART_ALL_IRQ_DISABLE (struct uart_port*) ; 
 int /*<<< orphan*/  UART_RX_IRQ_ENABLE (struct uart_port*) ; 
 int /*<<< orphan*/  arc_serial_isr ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_port*) ; 

__attribute__((used)) static int arc_serial_startup(struct uart_port *port)
{
	/* Before we hook up the ISR, Disable all UART Interrupts */
	UART_ALL_IRQ_DISABLE(port);

	if (request_irq(port->irq, arc_serial_isr, 0, "arc uart rx-tx", port)) {
		dev_warn(port->dev, "Unable to attach ARC UART intr\n");
		return -EBUSY;
	}

	UART_RX_IRQ_ENABLE(port); /* Only Rx IRQ enabled to begin with */

	return 0;
}