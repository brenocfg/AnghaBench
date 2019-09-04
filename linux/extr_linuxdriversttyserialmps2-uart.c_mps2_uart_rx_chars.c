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
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  rx; } ;
struct uart_port {TYPE_2__* state; TYPE_1__ icount; } ;
struct tty_port {int dummy; } ;
struct TYPE_4__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  UARTn_DATA ; 
 int /*<<< orphan*/  UARTn_STATE ; 
 int UARTn_STATE_RX_FULL ; 
 int mps2_uart_read8 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mps2_uart_rx_chars(struct uart_port *port)
{
	struct tty_port *tport = &port->state->port;

	while (mps2_uart_read8(port, UARTn_STATE) & UARTn_STATE_RX_FULL) {
		u8 rxdata = mps2_uart_read8(port, UARTn_DATA);

		port->icount.rx++;
		tty_insert_flip_char(&port->state->port, rxdata, TTY_NORMAL);
	}

	tty_flip_buffer_push(tport);
}