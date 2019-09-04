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
struct TYPE_4__ {int rx; int /*<<< orphan*/  parity; int /*<<< orphan*/  frame; } ;
struct uart_port {scalar_t__ type; TYPE_2__ icount; int /*<<< orphan*/  dev; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 scalar_t__ PORT_SCI ; 
 int /*<<< orphan*/  SCxRDR ; 
 int /*<<< orphan*/  SCxSR ; 
 unsigned short SCxSR_FER (struct uart_port*) ; 
 unsigned short SCxSR_PER (struct uart_port*) ; 
 unsigned short SCxSR_RDxF (struct uart_port*) ; 
 int /*<<< orphan*/  SCxSR_RDxF_CLEAR (struct uart_port*) ; 
 unsigned char TTY_FRAME ; 
 unsigned char TTY_NORMAL ; 
 unsigned char TTY_PARITY ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sci_clear_SCxSR (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_rxfill (struct uart_port*) ; 
 void* serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int tty_buffer_request_room (struct tty_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,char,unsigned char) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,char) ; 

__attribute__((used)) static void sci_receive_chars(struct uart_port *port)
{
	struct tty_port *tport = &port->state->port;
	int i, count, copied = 0;
	unsigned short status;
	unsigned char flag;

	status = serial_port_in(port, SCxSR);
	if (!(status & SCxSR_RDxF(port)))
		return;

	while (1) {
		/* Don't copy more bytes than there is room for in the buffer */
		count = tty_buffer_request_room(tport, sci_rxfill(port));

		/* If for any reason we can't copy more data, we're done! */
		if (count == 0)
			break;

		if (port->type == PORT_SCI) {
			char c = serial_port_in(port, SCxRDR);
			if (uart_handle_sysrq_char(port, c))
				count = 0;
			else
				tty_insert_flip_char(tport, c, TTY_NORMAL);
		} else {
			for (i = 0; i < count; i++) {
				char c = serial_port_in(port, SCxRDR);

				status = serial_port_in(port, SCxSR);
				if (uart_handle_sysrq_char(port, c)) {
					count--; i--;
					continue;
				}

				/* Store data and status */
				if (status & SCxSR_FER(port)) {
					flag = TTY_FRAME;
					port->icount.frame++;
					dev_notice(port->dev, "frame error\n");
				} else if (status & SCxSR_PER(port)) {
					flag = TTY_PARITY;
					port->icount.parity++;
					dev_notice(port->dev, "parity error\n");
				} else
					flag = TTY_NORMAL;

				tty_insert_flip_char(tport, c, flag);
			}
		}

		serial_port_in(port, SCxSR); /* dummy read */
		sci_clear_SCxSR(port, SCxSR_RDxF_CLEAR(port));

		copied += count;
		port->icount.rx += count;
	}

	if (copied) {
		/* Tell the rest of the system the news. New characters! */
		tty_flip_buffer_push(tport);
	} else {
		/* TTY buffers full; read from RX reg to prevent lockup */
		serial_port_in(port, SCxRDR);
		serial_port_in(port, SCxSR); /* dummy read */
		sci_clear_SCxSR(port, SCxSR_RDxF_CLEAR(port));
	}
}