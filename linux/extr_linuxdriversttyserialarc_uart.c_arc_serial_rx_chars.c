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
struct TYPE_3__ {int /*<<< orphan*/  rx; int /*<<< orphan*/  frame; int /*<<< orphan*/  overrun; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_2__* state; TYPE_1__ icount; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 unsigned int RXEMPTY ; 
 unsigned int RXFERR ; 
 unsigned int RXOERR ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_OVERRUN ; 
 int /*<<< orphan*/  UART_CLR_STATUS (struct uart_port*,unsigned int) ; 
 unsigned int UART_GET_DATA (struct uart_port*) ; 
 unsigned int UART_GET_STATUS (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static void arc_serial_rx_chars(struct uart_port *port, unsigned int status)
{
	unsigned int ch, flg = 0;

	/*
	 * UART has 4 deep RX-FIFO. Driver's recongnition of this fact
	 * is very subtle. Here's how ...
	 * Upon getting a RX-Intr, such that RX-EMPTY=0, meaning data available,
	 * driver reads the DATA Reg and keeps doing that in a loop, until
	 * RX-EMPTY=1. Multiple chars being avail, with a single Interrupt,
	 * before RX-EMPTY=0, implies some sort of buffering going on in the
	 * controller, which is indeed the Rx-FIFO.
	 */
	do {
		/*
		 * This could be an Rx Intr for err (no data),
		 * so check err and clear that Intr first
		 */
		if (unlikely(status & (RXOERR | RXFERR))) {
			if (status & RXOERR) {
				port->icount.overrun++;
				flg = TTY_OVERRUN;
				UART_CLR_STATUS(port, RXOERR);
			}

			if (status & RXFERR) {
				port->icount.frame++;
				flg = TTY_FRAME;
				UART_CLR_STATUS(port, RXFERR);
			}
		} else
			flg = TTY_NORMAL;

		if (status & RXEMPTY)
			continue;

		ch = UART_GET_DATA(port);
		port->icount.rx++;

		if (!(uart_handle_sysrq_char(port, ch)))
			uart_insert_char(port, status, RXOERR, ch, flg);

		spin_unlock(&port->lock);
		tty_flip_buffer_push(&port->state->port);
		spin_lock(&port->lock);
	} while (!((status = UART_GET_STATUS(port)) & RXEMPTY));
}