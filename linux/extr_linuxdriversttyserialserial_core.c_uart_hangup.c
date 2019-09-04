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
struct tty_port {int /*<<< orphan*/  mutex; int /*<<< orphan*/  delta_msr_wait; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  lock; scalar_t__ count; } ;
struct uart_state {struct tty_port port; } ;
struct uart_port {int dummy; } ;
struct tty_struct {int /*<<< orphan*/  index; struct uart_state* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_PM_STATE_OFF ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tty_port_active (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_set_active (struct tty_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_tty_set (struct tty_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_change_pm (struct uart_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_console (struct uart_port*) ; 
 int /*<<< orphan*/  uart_flush_buffer (struct tty_struct*) ; 
 struct uart_port* uart_port_check (struct uart_state*) ; 
 int /*<<< orphan*/  uart_shutdown (struct tty_struct*,struct uart_state*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uart_hangup(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;
	struct tty_port *port = &state->port;
	struct uart_port *uport;
	unsigned long flags;

	pr_debug("uart_hangup(%d)\n", tty->index);

	mutex_lock(&port->mutex);
	uport = uart_port_check(state);
	WARN(!uport, "hangup of detached port!\n");

	if (tty_port_active(port)) {
		uart_flush_buffer(tty);
		uart_shutdown(tty, state);
		spin_lock_irqsave(&port->lock, flags);
		port->count = 0;
		spin_unlock_irqrestore(&port->lock, flags);
		tty_port_set_active(port, 0);
		tty_port_tty_set(port, NULL);
		if (uport && !uart_console(uport))
			uart_change_pm(state, UART_PM_STATE_OFF);
		wake_up_interruptible(&port->open_wait);
		wake_up_interruptible(&port->delta_msr_wait);
	}
	mutex_unlock(&port->mutex);
}