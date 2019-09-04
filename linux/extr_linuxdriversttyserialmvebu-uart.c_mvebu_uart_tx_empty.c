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
 unsigned int STAT_TX_FIFO_EMP ; 
 unsigned int TIOCSER_TEMT ; 
 scalar_t__ UART_STAT ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int mvebu_uart_tx_empty(struct uart_port *port)
{
	unsigned long flags;
	unsigned int st;

	spin_lock_irqsave(&port->lock, flags);
	st = readl(port->membase + UART_STAT);
	spin_unlock_irqrestore(&port->lock, flags);

	return (st & STAT_TX_FIFO_EMP) ? TIOCSER_TEMT : 0;
}