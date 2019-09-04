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
typedef  int u8 ;
struct uart_port {scalar_t__ membase; int /*<<< orphan*/  lock; } ;
struct console {size_t index; } ;

/* Variables and functions */
 scalar_t__ UA_STATUS ; 
 int UA_STATUS_TX_READY ; 
 struct uart_port** digicolor_ports ; 
 int /*<<< orphan*/  digicolor_uart_console_putchar ; 
 scalar_t__ oops_in_progress ; 
 int readb_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int spin_trylock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uart_console_write (struct uart_port*,char const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void digicolor_uart_console_write(struct console *co, const char *c,
					 unsigned n)
{
	struct uart_port *port = digicolor_ports[co->index];
	u8 status;
	unsigned long flags;
	int locked = 1;

	if (oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	else
		spin_lock_irqsave(&port->lock, flags);

	uart_console_write(port, c, n, digicolor_uart_console_putchar);

	if (locked)
		spin_unlock_irqrestore(&port->lock, flags);

	/* Wait for transmitter to become empty */
	do {
		status = readb_relaxed(port->membase + UA_STATUS);
	} while ((status & UA_STATUS_TX_READY) == 0);
}