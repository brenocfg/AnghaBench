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
 int ENODEV ; 
 int /*<<< orphan*/  asc_enable_rx_interrupts (struct uart_port*) ; 
 int /*<<< orphan*/  asc_interrupt ; 
 int /*<<< orphan*/  asc_port_name (struct uart_port*) ; 
 int /*<<< orphan*/  asc_transmit_chars (struct uart_port*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 

__attribute__((used)) static int asc_startup(struct uart_port *port)
{
	if (request_irq(port->irq, asc_interrupt, 0,
			asc_port_name(port), port)) {
		dev_err(port->dev, "cannot allocate irq.\n");
		return -ENODEV;
	}

	asc_transmit_chars(port);
	asc_enable_rx_interrupts(port);

	return 0;
}