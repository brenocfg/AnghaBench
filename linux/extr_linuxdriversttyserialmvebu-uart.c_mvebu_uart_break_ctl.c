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
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ membase; } ;

/* Variables and functions */
 unsigned int CTRL_SND_BRK_SEQ ; 
 scalar_t__ UART_CTRL (struct uart_port*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void mvebu_uart_break_ctl(struct uart_port *port, int brk)
{
	unsigned int ctl;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	ctl = readl(port->membase + UART_CTRL(port));
	if (brk == -1)
		ctl |= CTRL_SND_BRK_SEQ;
	else
		ctl &= ~CTRL_SND_BRK_SEQ;
	writel(ctl, port->membase + UART_CTRL(port));
	spin_unlock_irqrestore(&port->lock, flags);
}