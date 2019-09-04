#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tx; } ;
struct uart_port {TYPE_3__ icount; TYPE_2__* state; } ;
struct sirfsoc_uart_port {TYPE_1__* uart_reg; struct uart_port port; } ;
struct sirfsoc_register {int /*<<< orphan*/  sirfsoc_tx_fifo_data; int /*<<< orphan*/  sirfsoc_tx_fifo_status; } ;
struct sirfsoc_fifo_status {int (* ff_full ) (struct uart_port*) ;} ;
struct circ_buf {size_t tail; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {struct circ_buf xmit; } ;
struct TYPE_4__ {struct sirfsoc_fifo_status fifo_status; struct sirfsoc_register uart_reg; } ;

/* Variables and functions */
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int stub1 (struct uart_port*) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
sirfsoc_uart_pio_tx_chars(struct sirfsoc_uart_port *sirfport, int count)
{
	struct uart_port *port = &sirfport->port;
	struct sirfsoc_register *ureg = &sirfport->uart_reg->uart_reg;
	struct sirfsoc_fifo_status *ufifo_st = &sirfport->uart_reg->fifo_status;
	struct circ_buf *xmit = &port->state->xmit;
	unsigned int num_tx = 0;
	while (!uart_circ_empty(xmit) &&
		!(rd_regl(port, ureg->sirfsoc_tx_fifo_status) &
					ufifo_st->ff_full(port)) &&
		count--) {
		wr_regl(port, ureg->sirfsoc_tx_fifo_data,
				xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		num_tx++;
	}
	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);
	return num_tx;
}