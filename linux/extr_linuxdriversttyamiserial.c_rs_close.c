#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; struct serial_state* driver_data; } ;
struct tty_port {int /*<<< orphan*/ * tty; } ;
struct serial_state {int /*<<< orphan*/  timeout; int /*<<< orphan*/  read_status_mask; struct tty_port tport; } ;
struct file {int dummy; } ;
struct TYPE_2__ {void* intreq; void* intena; } ;

/* Variables and functions */
 void* IF_RBF ; 
 int /*<<< orphan*/  UART_LSR_DR ; 
 TYPE_1__ custom ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  rs_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  rs_wait_until_sent (struct tty_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ serial_paranoia_check (struct serial_state*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shutdown (struct tty_struct*,struct serial_state*) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_close_end (struct tty_port*,struct tty_struct*) ; 
 scalar_t__ tty_port_close_start (struct tty_port*,struct tty_struct*,struct file*) ; 
 scalar_t__ tty_port_initialized (struct tty_port*) ; 

__attribute__((used)) static void rs_close(struct tty_struct *tty, struct file * filp)
{
	struct serial_state *state = tty->driver_data;
	struct tty_port *port = &state->tport;

	if (serial_paranoia_check(state, tty->name, "rs_close"))
		return;

	if (tty_port_close_start(port, tty, filp) == 0)
		return;

	/*
	 * At this point we stop accepting input.  To do this, we
	 * disable the receive line status interrupts, and tell the
	 * interrupt driver to stop checking the data ready bit in the
	 * line status register.
	 */
	state->read_status_mask &= ~UART_LSR_DR;
	if (tty_port_initialized(port)) {
	        /* disable receive interrupts */
	        custom.intena = IF_RBF;
		mb();
		/* clear any pending receive interrupt */
		custom.intreq = IF_RBF;
		mb();

		/*
		 * Before we drop DTR, make sure the UART transmitter
		 * has completely drained; this is especially
		 * important if there is a transmit FIFO!
		 */
		rs_wait_until_sent(tty, state->timeout);
	}
	shutdown(tty, state);
	rs_flush_buffer(tty);
		
	tty_ldisc_flush(tty);
	port->tty = NULL;

	tty_port_close_end(port, tty);
}