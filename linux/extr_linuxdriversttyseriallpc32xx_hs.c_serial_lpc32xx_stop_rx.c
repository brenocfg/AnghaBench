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
struct uart_port {int /*<<< orphan*/  membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_HSUART_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_HSUART_IIR (int /*<<< orphan*/ ) ; 
 int LPC32XX_HSU_BRK_INT ; 
 int LPC32XX_HSU_ERR_INT_EN ; 
 int LPC32XX_HSU_FE_INT ; 
 int LPC32XX_HSU_RX_INT_EN ; 
 int LPC32XX_HSU_RX_OE_INT ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serial_lpc32xx_stop_rx(struct uart_port *port)
{
	u32 tmp;

	tmp = readl(LPC32XX_HSUART_CTRL(port->membase));
	tmp &= ~(LPC32XX_HSU_RX_INT_EN | LPC32XX_HSU_ERR_INT_EN);
	writel(tmp, LPC32XX_HSUART_CTRL(port->membase));

	writel((LPC32XX_HSU_BRK_INT | LPC32XX_HSU_RX_OE_INT |
		LPC32XX_HSU_FE_INT), LPC32XX_HSUART_IIR(port->membase));
}