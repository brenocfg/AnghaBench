#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; } ;
struct uart_port {TYPE_1__ icount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_CR ; 
 unsigned int ATMEL_US_FRAME ; 
 unsigned int ATMEL_US_OVRE ; 
 unsigned int ATMEL_US_PARE ; 
 int /*<<< orphan*/  ATMEL_US_RSTSTA ; 
 unsigned int ATMEL_US_RXBRK ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_pdc_rxerr(struct uart_port *port, unsigned int status)
{
	/* clear error */
	atmel_uart_writel(port, ATMEL_US_CR, ATMEL_US_RSTSTA);

	if (status & ATMEL_US_RXBRK) {
		/* ignore side-effect */
		status &= ~(ATMEL_US_PARE | ATMEL_US_FRAME);
		port->icount.brk++;
	}
	if (status & ATMEL_US_PARE)
		port->icount.parity++;
	if (status & ATMEL_US_FRAME)
		port->icount.frame++;
	if (status & ATMEL_US_OVRE)
		port->icount.overrun++;
}