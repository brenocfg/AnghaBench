#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty_port {int /*<<< orphan*/  delta_msr_wait; } ;
struct uart_state {struct tty_port port; } ;
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  icount; } ;
struct uart_icount {scalar_t__ rng; scalar_t__ dsr; scalar_t__ dcd; scalar_t__ cts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 unsigned long TIOCM_CD ; 
 unsigned long TIOCM_CTS ; 
 unsigned long TIOCM_DSR ; 
 unsigned long TIOCM_RNG ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  memcpy (struct uart_icount*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_enable_ms (struct uart_port*) ; 
 int /*<<< orphan*/  uart_port_deref (struct uart_port*) ; 
 struct uart_port* uart_port_ref (struct uart_state*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int uart_wait_modem_status(struct uart_state *state, unsigned long arg)
{
	struct uart_port *uport;
	struct tty_port *port = &state->port;
	DECLARE_WAITQUEUE(wait, current);
	struct uart_icount cprev, cnow;
	int ret;

	/*
	 * note the counters on entry
	 */
	uport = uart_port_ref(state);
	if (!uport)
		return -EIO;
	spin_lock_irq(&uport->lock);
	memcpy(&cprev, &uport->icount, sizeof(struct uart_icount));
	uart_enable_ms(uport);
	spin_unlock_irq(&uport->lock);

	add_wait_queue(&port->delta_msr_wait, &wait);
	for (;;) {
		spin_lock_irq(&uport->lock);
		memcpy(&cnow, &uport->icount, sizeof(struct uart_icount));
		spin_unlock_irq(&uport->lock);

		set_current_state(TASK_INTERRUPTIBLE);

		if (((arg & TIOCM_RNG) && (cnow.rng != cprev.rng)) ||
		    ((arg & TIOCM_DSR) && (cnow.dsr != cprev.dsr)) ||
		    ((arg & TIOCM_CD)  && (cnow.dcd != cprev.dcd)) ||
		    ((arg & TIOCM_CTS) && (cnow.cts != cprev.cts))) {
			ret = 0;
			break;
		}

		schedule();

		/* see if a signal did it */
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}

		cprev = cnow;
	}
	__set_current_state(TASK_RUNNING);
	remove_wait_queue(&port->delta_msr_wait, &wait);
	uart_port_deref(uport);

	return ret;
}