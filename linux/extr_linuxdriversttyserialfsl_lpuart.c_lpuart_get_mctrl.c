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
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_RTS ; 
 scalar_t__ UARTMODEM ; 
 unsigned char UARTMODEM_RXRTSE ; 
 unsigned char UARTMODEM_TXCTSE ; 
 unsigned char readb (scalar_t__) ; 

__attribute__((used)) static unsigned int lpuart_get_mctrl(struct uart_port *port)
{
	unsigned int temp = 0;
	unsigned char reg;

	reg = readb(port->membase + UARTMODEM);
	if (reg & UARTMODEM_TXCTSE)
		temp |= TIOCM_CTS;

	if (reg & UARTMODEM_RXRTSE)
		temp |= TIOCM_RTS;

	return temp;
}