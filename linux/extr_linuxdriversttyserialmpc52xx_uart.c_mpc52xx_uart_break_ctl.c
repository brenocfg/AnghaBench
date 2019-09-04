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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* command ) (struct uart_port*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MPC52xx_PSC_START_BRK ; 
 int /*<<< orphan*/  MPC52xx_PSC_STOP_BRK ; 
 TYPE_1__* psc_ops ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mpc52xx_uart_break_ctl(struct uart_port *port, int ctl)
{
	unsigned long flags;
	spin_lock_irqsave(&port->lock, flags);

	if (ctl == -1)
		psc_ops->command(port, MPC52xx_PSC_START_BRK);
	else
		psc_ops->command(port, MPC52xx_PSC_STOP_BRK);

	spin_unlock_irqrestore(&port->lock, flags);
}