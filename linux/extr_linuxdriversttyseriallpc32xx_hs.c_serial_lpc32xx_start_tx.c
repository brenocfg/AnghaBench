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
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {int /*<<< orphan*/  membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_HSUART_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_HSU_TX_INT_EN ; 
 int /*<<< orphan*/  __serial_lpc32xx_tx (struct uart_port*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serial_lpc32xx_start_tx(struct uart_port *port)
{
	u32 tmp;

	__serial_lpc32xx_tx(port);
	tmp = readl(LPC32XX_HSUART_CTRL(port->membase));
	tmp |= LPC32XX_HSU_TX_INT_EN;
	writel(tmp, LPC32XX_HSUART_CTRL(port->membase));
}