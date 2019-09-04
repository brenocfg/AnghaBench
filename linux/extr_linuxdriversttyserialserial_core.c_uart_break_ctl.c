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
struct uart_port {scalar_t__ type; TYPE_1__* ops; } ;
struct tty_struct {struct uart_state* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* break_ctl ) (struct uart_port*,int) ;} ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ PORT_UNKNOWN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,int) ; 
 struct uart_port* uart_port_check (struct uart_state*) ; 

__attribute__((used)) static int uart_break_ctl(struct tty_struct *tty, int break_state)
{
	struct uart_state *state = tty->driver_data;
	struct tty_port *port = &state->port;
	struct uart_port *uport;
	int ret = -EIO;

	mutex_lock(&port->mutex);
	uport = uart_port_check(state);
	if (!uport)
		goto out;

	if (uport->type != PORT_UNKNOWN)
		uport->ops->break_ctl(uport, break_state);
	ret = 0;
out:
	mutex_unlock(&port->mutex);
	return ret;
}