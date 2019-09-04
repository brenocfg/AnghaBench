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
struct console {size_t index; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ sysrq; } ;
struct ar933x_uart_port {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int AR933X_UART_INT_ALLINTS ; 
 int /*<<< orphan*/  AR933X_UART_INT_EN_REG ; 
 int /*<<< orphan*/  AR933X_UART_INT_REG ; 
 struct ar933x_uart_port** ar933x_console_ports ; 
 int /*<<< orphan*/  ar933x_uart_console_putchar ; 
 unsigned int ar933x_uart_read (struct ar933x_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar933x_uart_wait_xmitr (struct ar933x_uart_port*) ; 
 int /*<<< orphan*/  ar933x_uart_write (struct ar933x_uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ oops_in_progress ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_console_write (TYPE_1__*,char const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar933x_uart_console_write(struct console *co, const char *s,
				      unsigned int count)
{
	struct ar933x_uart_port *up = ar933x_console_ports[co->index];
	unsigned long flags;
	unsigned int int_en;
	int locked = 1;

	local_irq_save(flags);

	if (up->port.sysrq)
		locked = 0;
	else if (oops_in_progress)
		locked = spin_trylock(&up->port.lock);
	else
		spin_lock(&up->port.lock);

	/*
	 * First save the IER then disable the interrupts
	 */
	int_en = ar933x_uart_read(up, AR933X_UART_INT_EN_REG);
	ar933x_uart_write(up, AR933X_UART_INT_EN_REG, 0);

	uart_console_write(&up->port, s, count, ar933x_uart_console_putchar);

	/*
	 * Finally, wait for transmitter to become empty
	 * and restore the IER
	 */
	ar933x_uart_wait_xmitr(up);
	ar933x_uart_write(up, AR933X_UART_INT_EN_REG, int_en);

	ar933x_uart_write(up, AR933X_UART_INT_REG, AR933X_UART_INT_ALLINTS);

	if (locked)
		spin_unlock(&up->port.lock);

	local_irq_restore(flags);
}