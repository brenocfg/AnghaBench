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
struct uart_port {TYPE_2__ icount; scalar_t__ membase; scalar_t__ x_char; TYPE_1__* state; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int UART_XMIT_SIZE ; 
 scalar_t__ VT8500_TXFIFO ; 
 int /*<<< orphan*/  VT8500_URFIDX ; 
 scalar_t__ WAKEUP_CHARS ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int vt8500_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt8500_stop_tx (struct uart_port*) ; 
 int /*<<< orphan*/  writeb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void handle_tx(struct uart_port *port)
{
	struct circ_buf *xmit = &port->state->xmit;

	if (port->x_char) {
		writeb(port->x_char, port->membase + VT8500_TXFIFO);
		port->icount.tx++;
		port->x_char = 0;
	}
	if (uart_circ_empty(xmit) || uart_tx_stopped(port)) {
		vt8500_stop_tx(port);
		return;
	}

	while ((vt8500_read(port, VT8500_URFIDX) & 0x1f) < 16) {
		if (uart_circ_empty(xmit))
			break;

		writeb(xmit->buf[xmit->tail], port->membase + VT8500_TXFIFO);

		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	if (uart_circ_empty(xmit))
		vt8500_stop_tx(port);
}