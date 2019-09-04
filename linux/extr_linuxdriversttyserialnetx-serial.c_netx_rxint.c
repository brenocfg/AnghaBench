#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  rx; } ;
struct uart_port {unsigned char read_status_mask; int /*<<< orphan*/  lock; TYPE_2__* state; TYPE_1__ icount; scalar_t__ membase; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 unsigned char FR_RXFE ; 
 unsigned char SR_BE ; 
 unsigned char SR_FE ; 
 unsigned char SR_OE ; 
 unsigned char SR_PE ; 
 unsigned char TTY_BREAK ; 
 unsigned char TTY_FRAME ; 
 unsigned char TTY_NORMAL ; 
 unsigned char TTY_PARITY ; 
 scalar_t__ UART_DR ; 
 scalar_t__ UART_FR ; 
 scalar_t__ UART_SR ; 
 unsigned char readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned char) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 scalar_t__ unlikely (unsigned char) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void netx_rxint(struct uart_port *port, unsigned long *flags)
{
	unsigned char rx, flg, status;

	while (!(readl(port->membase + UART_FR) & FR_RXFE)) {
		rx = readl(port->membase + UART_DR);
		flg = TTY_NORMAL;
		port->icount.rx++;
		status = readl(port->membase + UART_SR);
		if (status & SR_BE) {
			writel(0, port->membase + UART_SR);
			if (uart_handle_break(port))
				continue;
		}

		if (unlikely(status & (SR_FE | SR_PE | SR_OE))) {

			if (status & SR_PE)
				port->icount.parity++;
			else if (status & SR_FE)
				port->icount.frame++;
			if (status & SR_OE)
				port->icount.overrun++;

			status &= port->read_status_mask;

			if (status & SR_BE)
				flg = TTY_BREAK;
			else if (status & SR_PE)
				flg = TTY_PARITY;
			else if (status & SR_FE)
				flg = TTY_FRAME;
		}

		if (uart_handle_sysrq_char(port, rx))
			continue;

		uart_insert_char(port, status, SR_OE, rx, flg);
	}

	spin_unlock_irqrestore(&port->lock, *flags);
	tty_flip_buffer_push(&port->state->port);
	spin_lock_irqsave(&port->lock, *flags);
}