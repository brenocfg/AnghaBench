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
 int /*<<< orphan*/  KS8695_IRQ_UART_TX ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_enable (struct uart_port*,int) ; 
 int /*<<< orphan*/  tx_enabled (struct uart_port*) ; 

__attribute__((used)) static void ks8695uart_start_tx(struct uart_port *port)
{
	if (!tx_enabled(port)) {
		enable_irq(KS8695_IRQ_UART_TX);
		tx_enable(port, 1);
	}
}