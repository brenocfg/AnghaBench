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
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  UARTMODIR ; 
 unsigned long UARTMODIR_RXRTSE ; 
 unsigned long UARTMODIR_TXCTSE ; 
 unsigned long lpuart32_read (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int lpuart32_get_mctrl(struct uart_port *port)
{
	unsigned int temp = 0;
	unsigned long reg;

	reg = lpuart32_read(port, UARTMODIR);
	if (reg & UARTMODIR_TXCTSE)
		temp |= TIOCM_CTS;

	if (reg & UARTMODIR_RXRTSE)
		temp |= TIOCM_RTS;

	return temp;
}