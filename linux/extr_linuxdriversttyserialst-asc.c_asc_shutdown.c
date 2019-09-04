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
struct uart_port {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  asc_disable_rx_interrupts (struct uart_port*) ; 
 int /*<<< orphan*/  asc_disable_tx_interrupts (struct uart_port*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 

__attribute__((used)) static void asc_shutdown(struct uart_port *port)
{
	asc_disable_tx_interrupts(port);
	asc_disable_rx_interrupts(port);
	free_irq(port->irq, port);
}