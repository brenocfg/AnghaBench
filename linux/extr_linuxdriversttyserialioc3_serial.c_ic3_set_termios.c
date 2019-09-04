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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct ktermios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioc3_change_speed (struct uart_port*,struct ktermios*,struct ktermios*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
ic3_set_termios(struct uart_port *the_port,
		struct ktermios *termios, struct ktermios *old_termios)
{
	unsigned long port_flags;

	spin_lock_irqsave(&the_port->lock, port_flags);
	ioc3_change_speed(the_port, termios, old_termios);
	spin_unlock_irqrestore(&the_port->lock, port_flags);
}