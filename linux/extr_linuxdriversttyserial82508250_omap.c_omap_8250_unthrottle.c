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
struct uart_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; struct omap8250_priv* private_data; } ;
struct uart_8250_port {int ier; TYPE_1__* dma; } ;
struct omap8250_priv {int throttled; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rx_dma ) (struct uart_8250_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct uart_8250_port*) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void omap_8250_unthrottle(struct uart_port *port)
{
	struct omap8250_priv *priv = port->private_data;
	struct uart_8250_port *up = up_to_u8250p(port);
	unsigned long flags;

	pm_runtime_get_sync(port->dev);

	spin_lock_irqsave(&port->lock, flags);
	priv->throttled = false;
	if (up->dma)
		up->dma->rx_dma(up);
	up->ier |= UART_IER_RLSI | UART_IER_RDI;
	serial_out(up, UART_IER, up->ier);
	spin_unlock_irqrestore(&port->lock, flags);

	pm_runtime_mark_last_busy(port->dev);
	pm_runtime_put_autosuspend(port->dev);
}