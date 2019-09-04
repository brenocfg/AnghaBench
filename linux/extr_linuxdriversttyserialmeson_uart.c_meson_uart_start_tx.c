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
typedef  unsigned int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  tx; } ;
struct uart_port {unsigned int x_char; scalar_t__ membase; TYPE_2__ icount; TYPE_1__* state; } ;
struct circ_buf {unsigned int* buf; size_t tail; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 scalar_t__ AML_UART_CONTROL ; 
 scalar_t__ AML_UART_STATUS ; 
 unsigned int AML_UART_TX_FULL ; 
 unsigned int AML_UART_TX_INT_EN ; 
 scalar_t__ AML_UART_WFIFO ; 
 int SERIAL_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  meson_uart_stop_tx (struct uart_port*) ; 
 unsigned int readl (scalar_t__) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void meson_uart_start_tx(struct uart_port *port)
{
	struct circ_buf *xmit = &port->state->xmit;
	unsigned int ch;
	u32 val;

	if (uart_tx_stopped(port)) {
		meson_uart_stop_tx(port);
		return;
	}

	while (!(readl(port->membase + AML_UART_STATUS) & AML_UART_TX_FULL)) {
		if (port->x_char) {
			writel(port->x_char, port->membase + AML_UART_WFIFO);
			port->icount.tx++;
			port->x_char = 0;
			continue;
		}

		if (uart_circ_empty(xmit))
			break;

		ch = xmit->buf[xmit->tail];
		writel(ch, port->membase + AML_UART_WFIFO);
		xmit->tail = (xmit->tail+1) & (SERIAL_XMIT_SIZE - 1);
		port->icount.tx++;
	}

	if (!uart_circ_empty(xmit)) {
		val = readl(port->membase + AML_UART_CONTROL);
		val |= AML_UART_TX_INT_EN;
		writel(val, port->membase + AML_UART_CONTROL);
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);
}