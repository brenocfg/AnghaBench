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
struct uart_port {int /*<<< orphan*/  lock; TYPE_2__ icount; scalar_t__ membase; scalar_t__ x_char; TYPE_1__* state; } ;
struct circ_buf {size_t tail; int /*<<< orphan*/ * buf; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int UART_XMIT_SIZE ; 
 scalar_t__ UA_EMI_REC ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  digicolor_uart_stop_tx (struct uart_port*) ; 
 scalar_t__ digicolor_uart_tx_full (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writeb_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void digicolor_uart_tx(struct uart_port *port)
{
	struct circ_buf *xmit = &port->state->xmit;
	unsigned long flags;

	if (digicolor_uart_tx_full(port))
		return;

	spin_lock_irqsave(&port->lock, flags);

	if (port->x_char) {
		writeb_relaxed(port->x_char, port->membase + UA_EMI_REC);
		port->icount.tx++;
		port->x_char = 0;
		goto out;
	}

	if (uart_circ_empty(xmit) || uart_tx_stopped(port)) {
		digicolor_uart_stop_tx(port);
		goto out;
	}

	while (!uart_circ_empty(xmit)) {
		writeb(xmit->buf[xmit->tail], port->membase + UA_EMI_REC);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;

		if (digicolor_uart_tx_full(port))
			break;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

out:
	spin_unlock_irqrestore(&port->lock, flags);
}