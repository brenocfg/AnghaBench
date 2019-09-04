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
 unsigned int BOTH_EMPTY ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  UART_TX ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned int serial8250_early_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial8250_early_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void serial_putc(struct uart_port *port, int c)
{
	unsigned int status;

	serial8250_early_out(port, UART_TX, c);

	for (;;) {
		status = serial8250_early_in(port, UART_LSR);
		if ((status & BOTH_EMPTY) == BOTH_EMPTY)
			break;
		cpu_relax();
	}
}