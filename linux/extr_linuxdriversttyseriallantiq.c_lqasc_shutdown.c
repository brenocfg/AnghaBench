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
struct uart_port {scalar_t__ membase; } ;
struct ltq_uart_port {int /*<<< orphan*/  clk; int /*<<< orphan*/  err_irq; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCRXFCON_RXFEN ; 
 int /*<<< orphan*/  ASCRXFCON_RXFFLU ; 
 int /*<<< orphan*/  ASCTXFCON_TXFEN ; 
 int /*<<< orphan*/  ASCTXFCON_TXFFLU ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ LTQ_ASC_CON ; 
 scalar_t__ LTQ_ASC_RXFCON ; 
 scalar_t__ LTQ_ASC_TXFCON ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  ltq_w32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ltq_w32_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ltq_uart_port* to_ltq_uart_port (struct uart_port*) ; 

__attribute__((used)) static void
lqasc_shutdown(struct uart_port *port)
{
	struct ltq_uart_port *ltq_port = to_ltq_uart_port(port);
	free_irq(ltq_port->tx_irq, port);
	free_irq(ltq_port->rx_irq, port);
	free_irq(ltq_port->err_irq, port);

	ltq_w32(0, port->membase + LTQ_ASC_CON);
	ltq_w32_mask(ASCRXFCON_RXFEN, ASCRXFCON_RXFFLU,
		port->membase + LTQ_ASC_RXFCON);
	ltq_w32_mask(ASCTXFCON_TXFEN, ASCTXFCON_TXFFLU,
		port->membase + LTQ_ASC_TXFCON);
	if (!IS_ERR(ltq_port->clk))
		clk_disable(ltq_port->clk);
}