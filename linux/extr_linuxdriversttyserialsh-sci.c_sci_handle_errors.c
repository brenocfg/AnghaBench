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
struct TYPE_6__ {int /*<<< orphan*/  parity; int /*<<< orphan*/  frame; int /*<<< orphan*/  overrun; } ;
struct uart_port {int /*<<< orphan*/  dev; TYPE_3__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct sci_port {TYPE_2__* params; } ;
struct TYPE_5__ {unsigned short overrun_mask; } ;
struct TYPE_4__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCxSR ; 
 unsigned short SCxSR_FER (struct uart_port*) ; 
 unsigned short SCxSR_PER (struct uart_port*) ; 
 int /*<<< orphan*/  TTY_FRAME ; 
 int /*<<< orphan*/  TTY_OVERRUN ; 
 int /*<<< orphan*/  TTY_PARITY ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*) ; 
 unsigned short serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 scalar_t__ tty_insert_flip_char (struct tty_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sci_handle_errors(struct uart_port *port)
{
	int copied = 0;
	unsigned short status = serial_port_in(port, SCxSR);
	struct tty_port *tport = &port->state->port;
	struct sci_port *s = to_sci_port(port);

	/* Handle overruns */
	if (status & s->params->overrun_mask) {
		port->icount.overrun++;

		/* overrun error */
		if (tty_insert_flip_char(tport, 0, TTY_OVERRUN))
			copied++;

		dev_notice(port->dev, "overrun error\n");
	}

	if (status & SCxSR_FER(port)) {
		/* frame error */
		port->icount.frame++;

		if (tty_insert_flip_char(tport, 0, TTY_FRAME))
			copied++;

		dev_notice(port->dev, "frame error\n");
	}

	if (status & SCxSR_PER(port)) {
		/* parity error */
		port->icount.parity++;

		if (tty_insert_flip_char(tport, 0, TTY_PARITY))
			copied++;

		dev_notice(port->dev, "parity error\n");
	}

	if (copied)
		tty_flip_buffer_push(tport);

	return copied;
}