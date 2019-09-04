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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* handle_irq ) (struct uart_port*) ;} ;

/* Variables and functions */
 TYPE_1__* psc_ops ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 

__attribute__((used)) static irqreturn_t
mpc52xx_uart_int(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	irqreturn_t ret;

	spin_lock(&port->lock);

	ret = psc_ops->handle_irq(port);

	spin_unlock(&port->lock);

	return ret;
}