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
struct TYPE_3__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; int /*<<< orphan*/  buf_overrun; } ;
struct uart_port {unsigned int read_status_mask; unsigned int ignore_status_mask; TYPE_2__* state; TYPE_1__ icount; int /*<<< orphan*/  line; int /*<<< orphan*/  dev; } ;
struct sc16is7xx_port {unsigned int* buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 unsigned int SC16IS7XX_IIR_RLSE_SRC ; 
 unsigned int SC16IS7XX_LSR_BI_BIT ; 
 unsigned int SC16IS7XX_LSR_BRK_ERROR_MASK ; 
 unsigned int SC16IS7XX_LSR_FE_BIT ; 
 unsigned int SC16IS7XX_LSR_FIFOE_BIT ; 
 unsigned int SC16IS7XX_LSR_OE_BIT ; 
 unsigned int SC16IS7XX_LSR_PE_BIT ; 
 int /*<<< orphan*/  SC16IS7XX_LSR_REG ; 
 int /*<<< orphan*/  SC16IS7XX_RHR_REG ; 
 unsigned int TTY_BREAK ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_OVERRUN ; 
 unsigned int TTY_PARITY ; 
 struct sc16is7xx_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sc16is7xx_fifo_read (struct uart_port*,unsigned int) ; 
 void* sc16is7xx_port_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static void sc16is7xx_handle_rx(struct uart_port *port, unsigned int rxlen,
				unsigned int iir)
{
	struct sc16is7xx_port *s = dev_get_drvdata(port->dev);
	unsigned int lsr = 0, ch, flag, bytes_read, i;
	bool read_lsr = (iir == SC16IS7XX_IIR_RLSE_SRC) ? true : false;

	if (unlikely(rxlen >= sizeof(s->buf))) {
		dev_warn_ratelimited(port->dev,
				     "ttySC%i: Possible RX FIFO overrun: %d\n",
				     port->line, rxlen);
		port->icount.buf_overrun++;
		/* Ensure sanity of RX level */
		rxlen = sizeof(s->buf);
	}

	while (rxlen) {
		/* Only read lsr if there are possible errors in FIFO */
		if (read_lsr) {
			lsr = sc16is7xx_port_read(port, SC16IS7XX_LSR_REG);
			if (!(lsr & SC16IS7XX_LSR_FIFOE_BIT))
				read_lsr = false; /* No errors left in FIFO */
		} else
			lsr = 0;

		if (read_lsr) {
			s->buf[0] = sc16is7xx_port_read(port, SC16IS7XX_RHR_REG);
			bytes_read = 1;
		} else {
			sc16is7xx_fifo_read(port, rxlen);
			bytes_read = rxlen;
		}

		lsr &= SC16IS7XX_LSR_BRK_ERROR_MASK;

		port->icount.rx++;
		flag = TTY_NORMAL;

		if (unlikely(lsr)) {
			if (lsr & SC16IS7XX_LSR_BI_BIT) {
				port->icount.brk++;
				if (uart_handle_break(port))
					continue;
			} else if (lsr & SC16IS7XX_LSR_PE_BIT)
				port->icount.parity++;
			else if (lsr & SC16IS7XX_LSR_FE_BIT)
				port->icount.frame++;
			else if (lsr & SC16IS7XX_LSR_OE_BIT)
				port->icount.overrun++;

			lsr &= port->read_status_mask;
			if (lsr & SC16IS7XX_LSR_BI_BIT)
				flag = TTY_BREAK;
			else if (lsr & SC16IS7XX_LSR_PE_BIT)
				flag = TTY_PARITY;
			else if (lsr & SC16IS7XX_LSR_FE_BIT)
				flag = TTY_FRAME;
			else if (lsr & SC16IS7XX_LSR_OE_BIT)
				flag = TTY_OVERRUN;
		}

		for (i = 0; i < bytes_read; ++i) {
			ch = s->buf[i];
			if (uart_handle_sysrq_char(port, ch))
				continue;

			if (lsr & port->ignore_status_mask)
				continue;

			uart_insert_char(port, lsr, SC16IS7XX_LSR_OE_BIT, ch,
					 flag);
		}
		rxlen -= bytes_read;
	}

	tty_flip_buffer_push(&port->state->port);
}