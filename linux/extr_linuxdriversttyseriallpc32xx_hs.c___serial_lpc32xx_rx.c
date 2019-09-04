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
struct TYPE_3__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  rx; } ;
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  membase; TYPE_1__ icount; TYPE_2__* state; } ;
struct tty_port {int dummy; } ;
struct TYPE_4__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_HSUART_FIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_HSUART_IIR (int /*<<< orphan*/ ) ; 
 unsigned int LPC32XX_HSU_ERROR_DATA ; 
 int /*<<< orphan*/  LPC32XX_HSU_FE_INT ; 
 unsigned int LPC32XX_HSU_RX_EMPTY ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __serial_lpc32xx_rx(struct uart_port *port)
{
	struct tty_port *tport = &port->state->port;
	unsigned int tmp, flag;

	/* Read data from FIFO and push into terminal */
	tmp = readl(LPC32XX_HSUART_FIFO(port->membase));
	while (!(tmp & LPC32XX_HSU_RX_EMPTY)) {
		flag = TTY_NORMAL;
		port->icount.rx++;

		if (tmp & LPC32XX_HSU_ERROR_DATA) {
			/* Framing error */
			writel(LPC32XX_HSU_FE_INT,
			       LPC32XX_HSUART_IIR(port->membase));
			port->icount.frame++;
			flag = TTY_FRAME;
			tty_insert_flip_char(tport, 0, TTY_FRAME);
		}

		tty_insert_flip_char(tport, (tmp & 0xFF), flag);

		tmp = readl(LPC32XX_HSUART_FIFO(port->membase));
	}

	spin_unlock(&port->lock);
	tty_flip_buffer_push(tport);
	spin_lock(&port->lock);
}