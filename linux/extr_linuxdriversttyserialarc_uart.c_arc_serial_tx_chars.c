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
struct TYPE_4__ {int /*<<< orphan*/  tx; } ;
struct uart_port {unsigned char x_char; TYPE_2__ icount; TYPE_1__* state; } ;
struct circ_buf {unsigned char* buf; size_t tail; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int TXEMPTY ; 
 int UART_GET_STATUS (struct uart_port*) ; 
 int /*<<< orphan*/  UART_SET_DATA (struct uart_port*,unsigned char) ; 
 int /*<<< orphan*/  UART_TX_IRQ_ENABLE (struct uart_port*) ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 scalar_t__ unlikely (unsigned char) ; 

__attribute__((used)) static void arc_serial_tx_chars(struct uart_port *port)
{
	struct circ_buf *xmit = &port->state->xmit;
	int sent = 0;
	unsigned char ch;

	if (unlikely(port->x_char)) {
		UART_SET_DATA(port, port->x_char);
		port->icount.tx++;
		port->x_char = 0;
		sent = 1;
	} else if (!uart_circ_empty(xmit)) {
		ch = xmit->buf[xmit->tail];
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		while (!(UART_GET_STATUS(port) & TXEMPTY))
			cpu_relax();
		UART_SET_DATA(port, ch);
		sent = 1;
	}

	/*
	 * If num chars in xmit buffer are too few, ask tty layer for more.
	 * By Hard ISR to schedule processing in software interrupt part
	 */
	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	if (sent)
		UART_TX_IRQ_ENABLE(port);
}