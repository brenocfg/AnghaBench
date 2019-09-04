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
struct TYPE_2__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; int /*<<< orphan*/  line; int /*<<< orphan*/  dev; } ;
struct uart_omap_port {int /*<<< orphan*/  dev; TYPE_1__ port; scalar_t__ ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCM_OUT2 ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_SBC ; 
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_DR ; 
 int /*<<< orphan*/  UART_RX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_omap_port*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int serial_in (struct uart_omap_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_omap_clear_fifos (struct uart_omap_port*) ; 
 int /*<<< orphan*/  serial_omap_set_mctrl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_omap_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_omap_port* to_uart_omap_port (struct uart_port*) ; 

__attribute__((used)) static void serial_omap_shutdown(struct uart_port *port)
{
	struct uart_omap_port *up = to_uart_omap_port(port);
	unsigned long flags = 0;

	dev_dbg(up->port.dev, "serial_omap_shutdown+%d\n", up->port.line);

	pm_runtime_get_sync(up->dev);
	/*
	 * Disable interrupts from this port
	 */
	up->ier = 0;
	serial_out(up, UART_IER, 0);

	spin_lock_irqsave(&up->port.lock, flags);
	up->port.mctrl &= ~TIOCM_OUT2;
	serial_omap_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/*
	 * Disable break condition and FIFOs
	 */
	serial_out(up, UART_LCR, serial_in(up, UART_LCR) & ~UART_LCR_SBC);
	serial_omap_clear_fifos(up);

	/*
	 * Read data port to reset things, and then free the irq
	 */
	if (serial_in(up, UART_LSR) & UART_LSR_DR)
		(void) serial_in(up, UART_RX);

	pm_runtime_mark_last_busy(up->dev);
	pm_runtime_put_autosuspend(up->dev);
	free_irq(up->port.irq, up);
	dev_pm_clear_wake_irq(up->dev);
}