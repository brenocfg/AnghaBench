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
struct ktermios {int dummy; } ;

/* Variables and functions */
 int UART_DIV_MAX ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 

__attribute__((used)) static unsigned int serial8250_get_baud_rate(struct uart_port *port,
					     struct ktermios *termios,
					     struct ktermios *old)
{
	/*
	 * Ask the core to calculate the divisor for us.
	 * Allow 1% tolerance at the upper limit so uart clks marginally
	 * slower than nominal still match standard baud rates without
	 * causing transmission errors.
	 */
	return uart_get_baud_rate(port, termios, old,
				  port->uartclk / 16 / UART_DIV_MAX,
				  port->uartclk);
}