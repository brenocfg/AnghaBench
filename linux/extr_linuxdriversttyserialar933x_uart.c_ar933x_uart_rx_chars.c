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
struct tty_port {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx; } ;
struct TYPE_6__ {int ignore_status_mask; int /*<<< orphan*/  lock; TYPE_2__ icount; TYPE_1__* state; } ;
struct ar933x_uart_port {TYPE_3__ port; } ;
struct TYPE_4__ {struct tty_port port; } ;

/* Variables and functions */
 int AR933X_DUMMY_STATUS_RD ; 
 int /*<<< orphan*/  AR933X_UART_DATA_REG ; 
 unsigned int AR933X_UART_DATA_RX_CSR ; 
 unsigned int AR933X_UART_DATA_TX_RX_MASK ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 unsigned int ar933x_uart_read (struct ar933x_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar933x_uart_write (struct ar933x_uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,unsigned char,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_handle_sysrq_char (TYPE_3__*,unsigned char) ; 

__attribute__((used)) static void ar933x_uart_rx_chars(struct ar933x_uart_port *up)
{
	struct tty_port *port = &up->port.state->port;
	int max_count = 256;

	do {
		unsigned int rdata;
		unsigned char ch;

		rdata = ar933x_uart_read(up, AR933X_UART_DATA_REG);
		if ((rdata & AR933X_UART_DATA_RX_CSR) == 0)
			break;

		/* remove the character from the FIFO */
		ar933x_uart_write(up, AR933X_UART_DATA_REG,
				  AR933X_UART_DATA_RX_CSR);

		up->port.icount.rx++;
		ch = rdata & AR933X_UART_DATA_TX_RX_MASK;

		if (uart_handle_sysrq_char(&up->port, ch))
			continue;

		if ((up->port.ignore_status_mask & AR933X_DUMMY_STATUS_RD) == 0)
			tty_insert_flip_char(port, ch, TTY_NORMAL);
	} while (max_count-- > 0);

	spin_unlock(&up->port.lock);
	tty_flip_buffer_push(port);
	spin_lock(&up->port.lock);
}