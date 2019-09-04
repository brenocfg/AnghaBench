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
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS8695_IRQ_UART_RX ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_enable (struct uart_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ rx_enabled (struct uart_port*) ; 

__attribute__((used)) static void ks8695uart_stop_rx(struct uart_port *port)
{
	if (rx_enabled(port)) {
		disable_irq(KS8695_IRQ_UART_RX);
		rx_enable(port, 0);
	}
}