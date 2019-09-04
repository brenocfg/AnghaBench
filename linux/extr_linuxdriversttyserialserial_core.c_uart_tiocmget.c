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
struct tty_port {int /*<<< orphan*/  mutex; } ;
struct uart_state {struct tty_port port; } ;
struct uart_port {int mctrl; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct tty_struct {struct uart_state* driver_data; } ;
struct TYPE_2__ {int (* get_mctrl ) (struct uart_port*) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (struct uart_port*) ; 
 int /*<<< orphan*/  tty_io_error (struct tty_struct*) ; 
 struct uart_port* uart_port_check (struct uart_state*) ; 

__attribute__((used)) static int uart_tiocmget(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;
	struct tty_port *port = &state->port;
	struct uart_port *uport;
	int result = -EIO;

	mutex_lock(&port->mutex);
	uport = uart_port_check(state);
	if (!uport)
		goto out;

	if (!tty_io_error(tty)) {
		result = uport->mctrl;
		spin_lock_irq(&uport->lock);
		result |= uport->ops->get_mctrl(uport);
		spin_unlock_irq(&uport->lock);
	}
out:
	mutex_unlock(&port->mutex);
	return result;
}