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
struct uart_port {int line; TYPE_2__ icount; scalar_t__ x_char; TYPE_1__* state; } ;
struct sbd_port {struct uart_port port; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 unsigned int M_DUART_IMR_TX ; 
 int /*<<< orphan*/  R_DUART_IMRREG (int) ; 
 int /*<<< orphan*/  R_DUART_TX_HOLD ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 unsigned int read_sbdshr (struct sbd_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int /*<<< orphan*/  write_sbdchn (struct sbd_port*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  write_sbdshr (struct sbd_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void sbd_transmit_chars(struct sbd_port *sport)
{
	struct uart_port *uport = &sport->port;
	struct circ_buf *xmit = &sport->port.state->xmit;
	unsigned int mask;
	int stop_tx;

	/* XON/XOFF chars.  */
	if (sport->port.x_char) {
		write_sbdchn(sport, R_DUART_TX_HOLD, sport->port.x_char);
		sport->port.icount.tx++;
		sport->port.x_char = 0;
		return;
	}

	/* If nothing to do or stopped or hardware stopped.  */
	stop_tx = (uart_circ_empty(xmit) || uart_tx_stopped(&sport->port));

	/* Send char.  */
	if (!stop_tx) {
		write_sbdchn(sport, R_DUART_TX_HOLD, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->port.icount.tx++;

		if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
			uart_write_wakeup(&sport->port);
	}

	/* Are we are done?  */
	if (stop_tx || uart_circ_empty(xmit)) {
		/* Disable tx interrupts.  */
		mask = read_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2));
		mask &= ~M_DUART_IMR_TX;
		write_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2), mask);
	}
}