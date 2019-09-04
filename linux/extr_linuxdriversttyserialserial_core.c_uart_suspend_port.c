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
struct tty_port {int /*<<< orphan*/  mutex; } ;
struct uart_state {struct tty_port port; } ;
struct uart_port {int line; int suspended; int /*<<< orphan*/  cons; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; struct uart_ops* ops; int /*<<< orphan*/  irq; } ;
struct uart_ops {int /*<<< orphan*/  (* shutdown ) (struct uart_port*) ;int /*<<< orphan*/  (* tx_empty ) (struct uart_port*) ;int /*<<< orphan*/  (* stop_rx ) (struct uart_port*) ;int /*<<< orphan*/  (* set_mctrl ) (struct uart_port*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stop_tx ) (struct uart_port*) ;} ;
struct uart_match {struct uart_driver* member_1; struct uart_port* member_0; } ;
struct uart_driver {struct uart_state* state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_PM_STATE_OFF ; 
 int /*<<< orphan*/  console_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  console_suspend_enabled ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct device* device_find_child (int /*<<< orphan*/ ,struct uart_match*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_may_wakeup (struct device*) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  serial_match_port ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct uart_port*) ; 
 int /*<<< orphan*/  stub4 (struct uart_port*) ; 
 int /*<<< orphan*/  stub5 (struct uart_port*) ; 
 scalar_t__ tty_port_initialized (struct tty_port*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (struct tty_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_set_suspended (struct tty_port*,int) ; 
 int /*<<< orphan*/  uart_change_pm (struct uart_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_console (struct uart_port*) ; 

int uart_suspend_port(struct uart_driver *drv, struct uart_port *uport)
{
	struct uart_state *state = drv->state + uport->line;
	struct tty_port *port = &state->port;
	struct device *tty_dev;
	struct uart_match match = {uport, drv};

	mutex_lock(&port->mutex);

	tty_dev = device_find_child(uport->dev, &match, serial_match_port);
	if (tty_dev && device_may_wakeup(tty_dev)) {
		enable_irq_wake(uport->irq);
		put_device(tty_dev);
		mutex_unlock(&port->mutex);
		return 0;
	}
	put_device(tty_dev);

	/* Nothing to do if the console is not suspending */
	if (!console_suspend_enabled && uart_console(uport))
		goto unlock;

	uport->suspended = 1;

	if (tty_port_initialized(port)) {
		const struct uart_ops *ops = uport->ops;
		int tries;

		tty_port_set_suspended(port, 1);
		tty_port_set_initialized(port, 0);

		spin_lock_irq(&uport->lock);
		ops->stop_tx(uport);
		ops->set_mctrl(uport, 0);
		ops->stop_rx(uport);
		spin_unlock_irq(&uport->lock);

		/*
		 * Wait for the transmitter to empty.
		 */
		for (tries = 3; !ops->tx_empty(uport) && tries; tries--)
			msleep(10);
		if (!tries)
			dev_err(uport->dev, "%s: Unable to drain transmitter\n",
				uport->name);

		ops->shutdown(uport);
	}

	/*
	 * Disable the console device before suspending.
	 */
	if (uart_console(uport))
		console_stop(uport->cons);

	uart_change_pm(state, UART_PM_STATE_OFF);
unlock:
	mutex_unlock(&port->mutex);

	return 0;
}