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
typedef  scalar_t__ u32 ;
struct uart_port {scalar_t__ membase; } ;
struct men_z135_port {int /*<<< orphan*/  lock; struct uart_port port; } ;

/* Variables and functions */
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void men_z135_reg_clr(struct men_z135_port *uart,
				u32 addr, u32 val)
{
	struct uart_port *port = &uart->port;
	unsigned long flags;
	u32 reg;

	spin_lock_irqsave(&uart->lock, flags);

	reg = ioread32(port->membase + addr);
	reg &= ~val;
	iowrite32(reg, port->membase + addr);

	spin_unlock_irqrestore(&uart->lock, flags);
}