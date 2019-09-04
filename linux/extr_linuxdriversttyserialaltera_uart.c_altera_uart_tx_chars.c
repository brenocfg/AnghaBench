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
struct circ_buf {size_t head; size_t tail; scalar_t__* buf; } ;
struct altera_uart {int /*<<< orphan*/  imr; struct uart_port port; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_UART_CONTROL_TRDY_MSK ; 
 int /*<<< orphan*/  ALTERA_UART_STATUS_REG ; 
 int ALTERA_UART_STATUS_TRDY_MSK ; 
 int /*<<< orphan*/  ALTERA_UART_TXDATA_REG ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int altera_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  altera_uart_update_ctrl_reg (struct altera_uart*) ; 
 int /*<<< orphan*/  altera_uart_writel (struct uart_port*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 

__attribute__((used)) static void altera_uart_tx_chars(struct altera_uart *pp)
{
	struct uart_port *port = &pp->port;
	struct circ_buf *xmit = &port->state->xmit;

	if (port->x_char) {
		/* Send special char - probably flow control */
		altera_uart_writel(port, port->x_char, ALTERA_UART_TXDATA_REG);
		port->x_char = 0;
		port->icount.tx++;
		return;
	}

	while (altera_uart_readl(port, ALTERA_UART_STATUS_REG) &
	       ALTERA_UART_STATUS_TRDY_MSK) {
		if (xmit->head == xmit->tail)
			break;
		altera_uart_writel(port, xmit->buf[xmit->tail],
		       ALTERA_UART_TXDATA_REG);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	if (xmit->head == xmit->tail) {
		pp->imr &= ~ALTERA_UART_CONTROL_TRDY_MSK;
		altera_uart_update_ctrl_reg(pp);
	}
}