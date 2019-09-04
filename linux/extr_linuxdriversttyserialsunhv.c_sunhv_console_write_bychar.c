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
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ sysrq; } ;
struct console {int dummy; } ;

/* Variables and functions */
 scalar_t__ oops_in_progress ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int spin_trylock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sunhv_console_putchar (struct uart_port*,char) ; 
 struct uart_port* sunhv_port ; 

__attribute__((used)) static void sunhv_console_write_bychar(struct console *con, const char *s, unsigned n)
{
	struct uart_port *port = sunhv_port;
	unsigned long flags;
	int i, locked = 1;

	if (port->sysrq || oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	else
		spin_lock_irqsave(&port->lock, flags);

	for (i = 0; i < n; i++) {
		if (*s == '\n')
			sunhv_console_putchar(port, '\r');
		sunhv_console_putchar(port, *s++);
	}

	if (locked)
		spin_unlock_irqrestore(&port->lock, flags);
}