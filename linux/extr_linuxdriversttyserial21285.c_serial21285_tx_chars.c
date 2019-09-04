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
struct uart_port {TYPE_2__ icount; scalar_t__ x_char; TYPE_1__* state; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 scalar_t__* CSR_UARTDR ; 
 int* CSR_UARTFLG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  serial21285_stop_tx (struct uart_port*) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 

__attribute__((used)) static irqreturn_t serial21285_tx_chars(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	struct circ_buf *xmit = &port->state->xmit;
	int count = 256;

	if (port->x_char) {
		*CSR_UARTDR = port->x_char;
		port->icount.tx++;
		port->x_char = 0;
		goto out;
	}
	if (uart_circ_empty(xmit) || uart_tx_stopped(port)) {
		serial21285_stop_tx(port);
		goto out;
	}

	do {
		*CSR_UARTDR = xmit->buf[xmit->tail];
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		if (uart_circ_empty(xmit))
			break;
	} while (--count > 0 && !(*CSR_UARTFLG & 0x20));

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	if (uart_circ_empty(xmit))
		serial21285_stop_tx(port);

 out:
	return IRQ_HANDLED;
}