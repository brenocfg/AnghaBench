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
struct TYPE_4__ {int /*<<< orphan*/  brk; int /*<<< orphan*/  frame; int /*<<< orphan*/  overrun; int /*<<< orphan*/  rx; } ;
struct uart_port {int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; TYPE_2__ icount; scalar_t__ membase; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 int AML_UART_CLEAR_ERR ; 
 scalar_t__ AML_UART_CONTROL ; 
 int AML_UART_ERR ; 
 int AML_UART_FRAME_ERR ; 
 int AML_UART_PARITY_ERR ; 
 scalar_t__ AML_UART_RFIFO ; 
 int AML_UART_RX_EMPTY ; 
 scalar_t__ AML_UART_STATUS ; 
 int AML_UART_TX_FIFO_WERR ; 
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 char TTY_PARITY ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,int,char) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void meson_receive_chars(struct uart_port *port)
{
	struct tty_port *tport = &port->state->port;
	char flag;
	u32 ostatus, status, ch, mode;

	do {
		flag = TTY_NORMAL;
		port->icount.rx++;
		ostatus = status = readl(port->membase + AML_UART_STATUS);

		if (status & AML_UART_ERR) {
			if (status & AML_UART_TX_FIFO_WERR)
				port->icount.overrun++;
			else if (status & AML_UART_FRAME_ERR)
				port->icount.frame++;
			else if (status & AML_UART_PARITY_ERR)
				port->icount.frame++;

			mode = readl(port->membase + AML_UART_CONTROL);
			mode |= AML_UART_CLEAR_ERR;
			writel(mode, port->membase + AML_UART_CONTROL);

			/* It doesn't clear to 0 automatically */
			mode &= ~AML_UART_CLEAR_ERR;
			writel(mode, port->membase + AML_UART_CONTROL);

			status &= port->read_status_mask;
			if (status & AML_UART_FRAME_ERR)
				flag = TTY_FRAME;
			else if (status & AML_UART_PARITY_ERR)
				flag = TTY_PARITY;
		}

		ch = readl(port->membase + AML_UART_RFIFO);
		ch &= 0xff;

		if ((ostatus & AML_UART_FRAME_ERR) && (ch == 0)) {
			port->icount.brk++;
			flag = TTY_BREAK;
			if (uart_handle_break(port))
				continue;
		}

		if (uart_handle_sysrq_char(port, ch))
			continue;

		if ((status & port->ignore_status_mask) == 0)
			tty_insert_flip_char(tport, ch, flag);

		if (status & AML_UART_TX_FIFO_WERR)
			tty_insert_flip_char(tport, 0, TTY_OVERRUN);

	} while (!(readl(port->membase + AML_UART_STATUS) & AML_UART_RX_EMPTY));

	spin_unlock(&port->lock);
	tty_flip_buffer_push(tport);
	spin_lock(&port->lock);
}