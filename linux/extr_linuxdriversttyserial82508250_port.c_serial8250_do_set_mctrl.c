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
struct uart_8250_port {unsigned char mcr_mask; unsigned char mcr_force; unsigned char mcr; } ;

/* Variables and functions */
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_OUT1 ; 
 unsigned int TIOCM_OUT2 ; 
 unsigned int TIOCM_RTS ; 
 unsigned char UART_MCR_DTR ; 
 unsigned char UART_MCR_LOOP ; 
 unsigned char UART_MCR_OUT1 ; 
 unsigned char UART_MCR_OUT2 ; 
 unsigned char UART_MCR_RTS ; 
 int /*<<< orphan*/  serial8250_out_MCR (struct uart_8250_port*,unsigned char) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

void serial8250_do_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	unsigned char mcr = 0;

	if (mctrl & TIOCM_RTS)
		mcr |= UART_MCR_RTS;
	if (mctrl & TIOCM_DTR)
		mcr |= UART_MCR_DTR;
	if (mctrl & TIOCM_OUT1)
		mcr |= UART_MCR_OUT1;
	if (mctrl & TIOCM_OUT2)
		mcr |= UART_MCR_OUT2;
	if (mctrl & TIOCM_LOOP)
		mcr |= UART_MCR_LOOP;

	mcr = (mcr & up->mcr_mask) | up->mcr_force | up->mcr;

	serial8250_out_MCR(up, mcr);
}