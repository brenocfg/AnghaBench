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
struct uart_port {int uartclk; } ;
struct uart_8250_port {int capabilities; scalar_t__ canary; struct uart_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_LCR ; 
 int UART_NATSEMI ; 
 int /*<<< orphan*/  ns16550a_goto_highspeed (struct uart_8250_port*) ; 
 struct uart_8250_port* serial8250_ports ; 
 int /*<<< orphan*/  serial8250_reg ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_resume_port (int /*<<< orphan*/ *,struct uart_port*) ; 

void serial8250_resume_port(int line)
{
	struct uart_8250_port *up = &serial8250_ports[line];
	struct uart_port *port = &up->port;

	up->canary = 0;

	if (up->capabilities & UART_NATSEMI) {
		/* Ensure it's still in high speed mode */
		serial_port_out(port, UART_LCR, 0xE0);

		ns16550a_goto_highspeed(up);

		serial_port_out(port, UART_LCR, 0);
		port->uartclk = 921600*16;
	}
	uart_resume_port(&serial8250_reg, port);
}