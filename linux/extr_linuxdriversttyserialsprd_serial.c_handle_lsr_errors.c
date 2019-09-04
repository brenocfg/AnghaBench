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
struct uart_port {unsigned int read_status_mask; TYPE_1__ icount; } ;

/* Variables and functions */
 unsigned int SPRD_LSR_BI ; 
 unsigned int SPRD_LSR_FE ; 
 unsigned int SPRD_LSR_OE ; 
 unsigned int SPRD_LSR_PE ; 
 unsigned int TTY_BREAK ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_PARITY ; 
 int uart_handle_break (struct uart_port*) ; 

__attribute__((used)) static int handle_lsr_errors(struct uart_port *port,
			     unsigned int *flag,
			     unsigned int *lsr)
{
	int ret = 0;

	/* statistics */
	if (*lsr & SPRD_LSR_BI) {
		*lsr &= ~(SPRD_LSR_FE | SPRD_LSR_PE);
		port->icount.brk++;
		ret = uart_handle_break(port);
		if (ret)
			return ret;
	} else if (*lsr & SPRD_LSR_PE)
		port->icount.parity++;
	else if (*lsr & SPRD_LSR_FE)
		port->icount.frame++;
	if (*lsr & SPRD_LSR_OE)
		port->icount.overrun++;

	/* mask off conditions which should be ignored */
	*lsr &= port->read_status_mask;
	if (*lsr & SPRD_LSR_BI)
		*flag = TTY_BREAK;
	else if (*lsr & SPRD_LSR_PE)
		*flag = TTY_PARITY;
	else if (*lsr & SPRD_LSR_FE)
		*flag = TTY_FRAME;

	return ret;
}