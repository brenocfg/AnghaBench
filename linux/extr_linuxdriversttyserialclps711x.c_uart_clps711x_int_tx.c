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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  tx; } ;
struct uart_port {TYPE_2__ icount; scalar_t__ membase; int /*<<< orphan*/  irq; scalar_t__ x_char; TYPE_1__* state; int /*<<< orphan*/  dev; } ;
struct clps711x_port {int /*<<< orphan*/  syscon; scalar_t__ tx_enabled; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SYSFLG_OFFSET ; 
 int SYSFLG_UTXFF ; 
 scalar_t__ UARTDR_OFFSET ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 struct clps711x_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int /*<<< orphan*/  writew (scalar_t__,scalar_t__) ; 

__attribute__((used)) static irqreturn_t uart_clps711x_int_tx(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	struct clps711x_port *s = dev_get_drvdata(port->dev);
	struct circ_buf *xmit = &port->state->xmit;

	if (port->x_char) {
		writew(port->x_char, port->membase + UARTDR_OFFSET);
		port->icount.tx++;
		port->x_char = 0;
		return IRQ_HANDLED;
	}

	if (uart_circ_empty(xmit) || uart_tx_stopped(port)) {
		if (s->tx_enabled) {
			disable_irq_nosync(port->irq);
			s->tx_enabled = 0;
		}
		return IRQ_HANDLED;
	}

	while (!uart_circ_empty(xmit)) {
		u32 sysflg = 0;

		writew(xmit->buf[xmit->tail], port->membase + UARTDR_OFFSET);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;

		regmap_read(s->syscon, SYSFLG_OFFSET, &sysflg);
		if (sysflg & SYSFLG_UTXFF)
			break;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	return IRQ_HANDLED;
}