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
struct TYPE_6__ {char* buf; } ;
struct tty_port {int dummy; } ;
struct uart_state {TYPE_3__ xmit; struct tty_port port; } ;
struct uart_port {TYPE_1__* cons; } ;
struct TYPE_5__ {int /*<<< orphan*/  c_cflag; } ;
struct tty_struct {TYPE_2__ termios; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  cflag; } ;

/* Variables and functions */
 scalar_t__ C_HUPCL (struct tty_struct*) ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tty_port_initialized (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (struct tty_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_set_suspended (struct tty_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_console (struct uart_port*) ; 
 struct uart_port* uart_port_check (struct uart_state*) ; 
 int /*<<< orphan*/  uart_port_dtr_rts (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_port_lock (struct uart_state*,unsigned long) ; 
 int /*<<< orphan*/  uart_port_shutdown (struct tty_port*) ; 
 int /*<<< orphan*/  uart_port_unlock (struct uart_port*,unsigned long) ; 

__attribute__((used)) static void uart_shutdown(struct tty_struct *tty, struct uart_state *state)
{
	struct uart_port *uport = uart_port_check(state);
	struct tty_port *port = &state->port;
	unsigned long flags = 0;
	char *xmit_buf = NULL;

	/*
	 * Set the TTY IO error marker
	 */
	if (tty)
		set_bit(TTY_IO_ERROR, &tty->flags);

	if (tty_port_initialized(port)) {
		tty_port_set_initialized(port, 0);

		/*
		 * Turn off DTR and RTS early.
		 */
		if (uport && uart_console(uport) && tty)
			uport->cons->cflag = tty->termios.c_cflag;

		if (!tty || C_HUPCL(tty))
			uart_port_dtr_rts(uport, 0);

		uart_port_shutdown(port);
	}

	/*
	 * It's possible for shutdown to be called after suspend if we get
	 * a DCD drop (hangup) at just the right time.  Clear suspended bit so
	 * we don't try to resume a port that has been shutdown.
	 */
	tty_port_set_suspended(port, 0);

	/*
	 * Do not free() the transmit buffer page under the port lock since
	 * this can create various circular locking scenarios. For instance,
	 * console driver may need to allocate/free a debug object, which
	 * can endup in printk() recursion.
	 */
	uart_port_lock(state, flags);
	xmit_buf = state->xmit.buf;
	state->xmit.buf = NULL;
	uart_port_unlock(uport, flags);

	if (xmit_buf)
		free_page((unsigned long)xmit_buf);
}