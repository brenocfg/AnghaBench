#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct dz_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  dz_start_tx (TYPE_1__*) ; 
 int /*<<< orphan*/  dz_stop_tx (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dz_port* to_dport (struct uart_port*) ; 

__attribute__((used)) static void dz_pm(struct uart_port *uport, unsigned int state,
		  unsigned int oldstate)
{
	struct dz_port *dport = to_dport(uport);
	unsigned long flags;

	spin_lock_irqsave(&dport->port.lock, flags);
	if (state < 3)
		dz_start_tx(&dport->port);
	else
		dz_stop_tx(&dport->port);
	spin_unlock_irqrestore(&dport->port.lock, flags);
}