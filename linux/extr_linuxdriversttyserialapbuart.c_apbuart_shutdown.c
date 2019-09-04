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
 unsigned int UART_CTRL_RE ; 
 unsigned int UART_CTRL_RI ; 
 unsigned int UART_CTRL_TE ; 
 unsigned int UART_CTRL_TI ; 
 unsigned int UART_GET_CTRL (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_CTRL (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 

__attribute__((used)) static void apbuart_shutdown(struct uart_port *port)
{
	unsigned int cr;

	/* disable all interrupts, disable the port */
	cr = UART_GET_CTRL(port);
	UART_PUT_CTRL(port,
		      cr & ~(UART_CTRL_RE | UART_CTRL_TE |
			     UART_CTRL_RI | UART_CTRL_TI));

	/* Free the interrupt */
	free_irq(port->irq, port);
}