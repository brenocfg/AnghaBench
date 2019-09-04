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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct uart_omap_port {int ier; int /*<<< orphan*/  dev; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_omap_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_omap_port* to_uart_omap_port (struct uart_port*) ; 

__attribute__((used)) static void serial_omap_throttle(struct uart_port *port)
{
	struct uart_omap_port *up = to_uart_omap_port(port);
	unsigned long flags;

	pm_runtime_get_sync(up->dev);
	spin_lock_irqsave(&up->port.lock, flags);
	up->ier &= ~(UART_IER_RLSI | UART_IER_RDI);
	serial_out(up, UART_IER, up->ier);
	spin_unlock_irqrestore(&up->port.lock, flags);
	pm_runtime_mark_last_busy(up->dev);
	pm_runtime_put_autosuspend(up->dev);
}