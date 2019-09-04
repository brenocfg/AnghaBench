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
struct uart_port {scalar_t__ membase; TYPE_2__ icount; scalar_t__ x_char; TYPE_1__* state; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct altera_jtaguart {scalar_t__ imr; struct uart_port port; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 scalar_t__ ALTERA_JTAGUART_CONTROL_REG ; 
 scalar_t__ ALTERA_JTAGUART_CONTROL_WE_MSK ; 
 unsigned int ALTERA_JTAGUART_CONTROL_WSPACE_MSK ; 
 unsigned int ALTERA_JTAGUART_CONTROL_WSPACE_OFF ; 
 scalar_t__ ALTERA_JTAGUART_DATA_REG ; 
 int UART_XMIT_SIZE ; 
 unsigned int WAKEUP_CHARS ; 
 unsigned int readl (scalar_t__) ; 
 unsigned int uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void altera_jtaguart_tx_chars(struct altera_jtaguart *pp)
{
	struct uart_port *port = &pp->port;
	struct circ_buf *xmit = &port->state->xmit;
	unsigned int pending, count;

	if (port->x_char) {
		/* Send special char - probably flow control */
		writel(port->x_char, port->membase + ALTERA_JTAGUART_DATA_REG);
		port->x_char = 0;
		port->icount.tx++;
		return;
	}

	pending = uart_circ_chars_pending(xmit);
	if (pending > 0) {
		count = (readl(port->membase + ALTERA_JTAGUART_CONTROL_REG) &
				ALTERA_JTAGUART_CONTROL_WSPACE_MSK) >>
			ALTERA_JTAGUART_CONTROL_WSPACE_OFF;
		if (count > pending)
			count = pending;
		if (count > 0) {
			pending -= count;
			while (count--) {
				writel(xmit->buf[xmit->tail],
				       port->membase + ALTERA_JTAGUART_DATA_REG);
				xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
				port->icount.tx++;
			}
			if (pending < WAKEUP_CHARS)
				uart_write_wakeup(port);
		}
	}

	if (pending == 0) {
		pp->imr &= ~ALTERA_JTAGUART_CONTROL_WE_MSK;
		writel(pp->imr, port->membase + ALTERA_JTAGUART_CONTROL_REG);
	}
}