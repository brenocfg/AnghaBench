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
typedef  int u32 ;
struct uart_port {int /*<<< orphan*/  membase; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; int /*<<< orphan*/  mapbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_HSUART_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_HSUART_IIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_HSUART_RATE (int /*<<< orphan*/ ) ; 
 int LPC32XX_HSU_BRK_INT ; 
 int LPC32XX_HSU_ERR_INT_EN ; 
 int LPC32XX_HSU_FE_INT ; 
 int LPC32XX_HSU_OFFSET (int) ; 
 int LPC32XX_HSU_RX_INT_EN ; 
 int LPC32XX_HSU_RX_OE_INT ; 
 int LPC32XX_HSU_RX_TL32B ; 
 int LPC32XX_HSU_TMO_INACT_4B ; 
 int LPC32XX_HSU_TX_INT ; 
 int LPC32XX_HSU_TX_TL8B ; 
 int /*<<< orphan*/  MODNAME ; 
 int /*<<< orphan*/  __serial_uart_flush (struct uart_port*) ; 
 int /*<<< orphan*/  lpc32xx_loopback_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  serial_lpc32xx_interrupt ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serial_lpc32xx_startup(struct uart_port *port)
{
	int retval;
	unsigned long flags;
	u32 tmp;

	spin_lock_irqsave(&port->lock, flags);

	__serial_uart_flush(port);

	writel((LPC32XX_HSU_TX_INT | LPC32XX_HSU_FE_INT |
		LPC32XX_HSU_BRK_INT | LPC32XX_HSU_RX_OE_INT),
	       LPC32XX_HSUART_IIR(port->membase));

	writel(0xFF, LPC32XX_HSUART_RATE(port->membase));

	/*
	 * Set receiver timeout, HSU offset of 20, no break, no interrupts,
	 * and default FIFO trigger levels
	 */
	tmp = LPC32XX_HSU_TX_TL8B | LPC32XX_HSU_RX_TL32B |
		LPC32XX_HSU_OFFSET(20) | LPC32XX_HSU_TMO_INACT_4B;
	writel(tmp, LPC32XX_HSUART_CTRL(port->membase));

	lpc32xx_loopback_set(port->mapbase, 0); /* get out of loopback mode */

	spin_unlock_irqrestore(&port->lock, flags);

	retval = request_irq(port->irq, serial_lpc32xx_interrupt,
			     0, MODNAME, port);
	if (!retval)
		writel((tmp | LPC32XX_HSU_RX_INT_EN | LPC32XX_HSU_ERR_INT_EN),
		       LPC32XX_HSUART_CTRL(port->membase));

	return retval;
}