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
struct TYPE_2__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct uart_state {TYPE_1__ port; } ;
struct uart_port {int /*<<< orphan*/  lock; struct uart_state* state; } ;
struct ioc3_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ALL ; 
 struct ioc3_port* get_ioc3_port (struct uart_port*) ; 
 int /*<<< orphan*/  set_notification (struct ioc3_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ic3_shutdown(struct uart_port *the_port)
{
	unsigned long port_flags;
	struct ioc3_port *port;
	struct uart_state *state;

	port = get_ioc3_port(the_port);
	if (!port)
		return;

	state = the_port->state;
	wake_up_interruptible(&state->port.delta_msr_wait);

	spin_lock_irqsave(&the_port->lock, port_flags);
	set_notification(port, N_ALL, 0);
	spin_unlock_irqrestore(&the_port->lock, port_flags);
}