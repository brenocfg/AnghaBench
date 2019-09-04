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
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  rx; } ;
struct uart_port {unsigned int read_status_mask; unsigned int ignore_status_mask; TYPE_2__* state; TYPE_1__ icount; scalar_t__ membase; int /*<<< orphan*/  dev; } ;
struct clps711x_port {int /*<<< orphan*/  syscon; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SYSFLG_OFFSET ; 
 int SYSFLG_URXFE ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_OVERRUN ; 
 unsigned int TTY_PARITY ; 
 int UARTDR_FRMERR ; 
 scalar_t__ UARTDR_OFFSET ; 
 int UARTDR_OVERR ; 
 int UARTDR_PARERR ; 
 struct clps711x_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,int) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned int,int,int,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static irqreturn_t uart_clps711x_int_rx(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	struct clps711x_port *s = dev_get_drvdata(port->dev);
	unsigned int status, flg;
	u16 ch;

	for (;;) {
		u32 sysflg = 0;

		regmap_read(s->syscon, SYSFLG_OFFSET, &sysflg);
		if (sysflg & SYSFLG_URXFE)
			break;

		ch = readw(port->membase + UARTDR_OFFSET);
		status = ch & (UARTDR_FRMERR | UARTDR_PARERR | UARTDR_OVERR);
		ch &= 0xff;

		port->icount.rx++;
		flg = TTY_NORMAL;

		if (unlikely(status)) {
			if (status & UARTDR_PARERR)
				port->icount.parity++;
			else if (status & UARTDR_FRMERR)
				port->icount.frame++;
			else if (status & UARTDR_OVERR)
				port->icount.overrun++;

			status &= port->read_status_mask;

			if (status & UARTDR_PARERR)
				flg = TTY_PARITY;
			else if (status & UARTDR_FRMERR)
				flg = TTY_FRAME;
			else if (status & UARTDR_OVERR)
				flg = TTY_OVERRUN;
		}

		if (uart_handle_sysrq_char(port, ch))
			continue;

		if (status & port->ignore_status_mask)
			continue;

		uart_insert_char(port, status, UARTDR_OVERR, ch, flg);
	}

	tty_flip_buffer_push(&port->state->port);

	return IRQ_HANDLED;
}