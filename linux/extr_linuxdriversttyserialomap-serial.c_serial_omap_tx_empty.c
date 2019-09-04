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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  line; int /*<<< orphan*/  dev; } ;
struct uart_omap_port {int /*<<< orphan*/  dev; TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int TIOCSER_TEMT ; 
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_TEMT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int serial_in (struct uart_omap_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_omap_port* to_uart_omap_port (struct uart_port*) ; 

__attribute__((used)) static unsigned int serial_omap_tx_empty(struct uart_port *port)
{
	struct uart_omap_port *up = to_uart_omap_port(port);
	unsigned long flags = 0;
	unsigned int ret = 0;

	pm_runtime_get_sync(up->dev);
	dev_dbg(up->port.dev, "serial_omap_tx_empty+%d\n", up->port.line);
	spin_lock_irqsave(&up->port.lock, flags);
	ret = serial_in(up, UART_LSR) & UART_LSR_TEMT ? TIOCSER_TEMT : 0;
	spin_unlock_irqrestore(&up->port.lock, flags);
	pm_runtime_mark_last_busy(up->dev);
	pm_runtime_put_autosuspend(up->dev);
	return ret;
}