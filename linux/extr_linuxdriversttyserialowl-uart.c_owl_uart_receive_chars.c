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
struct TYPE_3__ {int /*<<< orphan*/  rx; int /*<<< orphan*/  frame; int /*<<< orphan*/  brk; int /*<<< orphan*/  overrun; } ;
struct uart_port {int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; TYPE_2__* state; TYPE_1__ icount; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  OWL_UART_CTL ; 
 int OWL_UART_CTL_TRFS_TX ; 
 int /*<<< orphan*/  OWL_UART_RXDAT ; 
 int /*<<< orphan*/  OWL_UART_STAT ; 
 int OWL_UART_STAT_RFEM ; 
 int OWL_UART_STAT_RXER ; 
 int OWL_UART_STAT_RXST ; 
 char TTY_NORMAL ; 
 char TTY_PARITY ; 
 int owl_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  owl_uart_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ *,int,char) ; 

__attribute__((used)) static void owl_uart_receive_chars(struct uart_port *port)
{
	u32 stat, val;

	val = owl_uart_read(port, OWL_UART_CTL);
	val &= ~OWL_UART_CTL_TRFS_TX;
	owl_uart_write(port, val, OWL_UART_CTL);

	stat = owl_uart_read(port, OWL_UART_STAT);
	while (!(stat & OWL_UART_STAT_RFEM)) {
		char flag = TTY_NORMAL;

		if (stat & OWL_UART_STAT_RXER)
			port->icount.overrun++;

		if (stat & OWL_UART_STAT_RXST) {
			/* We are not able to distinguish the error type. */
			port->icount.brk++;
			port->icount.frame++;

			stat &= port->read_status_mask;
			if (stat & OWL_UART_STAT_RXST)
				flag = TTY_PARITY;
		} else
			port->icount.rx++;

		val = owl_uart_read(port, OWL_UART_RXDAT);
		val &= 0xff;

		if ((stat & port->ignore_status_mask) == 0)
			tty_insert_flip_char(&port->state->port, val, flag);

		stat = owl_uart_read(port, OWL_UART_STAT);
	}

	spin_unlock(&port->lock);
	tty_flip_buffer_push(&port->state->port);
	spin_lock(&port->lock);
}