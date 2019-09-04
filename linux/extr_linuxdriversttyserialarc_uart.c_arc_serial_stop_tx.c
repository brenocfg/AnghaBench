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
 int TXEMPTY ; 
 int UART_GET_STATUS (struct uart_port*) ; 
 int /*<<< orphan*/  UART_TX_IRQ_DISABLE (struct uart_port*) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void arc_serial_stop_tx(struct uart_port *port)
{
	while (!(UART_GET_STATUS(port) & TXEMPTY))
		cpu_relax();

	UART_TX_IRQ_DISABLE(port);
}