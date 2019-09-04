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
struct TYPE_4__ {TYPE_1__* tty; int /*<<< orphan*/  delta_msr_wait; } ;
struct uart_state {TYPE_2__ port; } ;
struct uart_port {int /*<<< orphan*/  lock; struct uart_state* state; } ;
struct ioc4_port {int /*<<< orphan*/  ip_flags; int /*<<< orphan*/ * ip_port; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ALL ; 
 int /*<<< orphan*/  PORT_INACTIVE ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 struct ioc4_port* get_ioc4_port (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_notification (struct ioc4_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ic4_shutdown(struct uart_port *the_port)
{
	unsigned long port_flags;
	struct ioc4_port *port;
	struct uart_state *state;

	port = get_ioc4_port(the_port, 0);
	if (!port)
		return;

	state = the_port->state;
	port->ip_port = NULL;

	wake_up_interruptible(&state->port.delta_msr_wait);

	if (state->port.tty)
		set_bit(TTY_IO_ERROR, &state->port.tty->flags);

	spin_lock_irqsave(&the_port->lock, port_flags);
	set_notification(port, N_ALL, 0);
	port->ip_flags = PORT_INACTIVE;
	spin_unlock_irqrestore(&the_port->lock, port_flags);
}