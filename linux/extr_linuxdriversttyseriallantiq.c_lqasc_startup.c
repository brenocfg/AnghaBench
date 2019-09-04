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
struct uart_port {scalar_t__ membase; int /*<<< orphan*/  uartclk; } ;
struct ltq_uart_port {int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  err_irq; int /*<<< orphan*/  fpiclk; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int ASCCLC_DISS ; 
 int ASCCLC_RMCMASK ; 
 int ASCCLC_RMCOFFSET ; 
 int ASCCON_FEN ; 
 int ASCCON_M_8ASYNC ; 
 int ASCCON_ROEN ; 
 int ASCCON_TOEN ; 
 int ASCRXFCON_RXFEN ; 
 int ASCRXFCON_RXFFLU ; 
 int ASCRXFCON_RXFITLMASK ; 
 int ASCRXFCON_RXFITLOFF ; 
 int ASCTXFCON_TXFEN ; 
 int ASCTXFCON_TXFFLU ; 
 int ASCTXFCON_TXFITLMASK ; 
 int ASCTXFCON_TXFITLOFF ; 
 int ASC_IRNREN_ERR ; 
 int ASC_IRNREN_RX ; 
 int ASC_IRNREN_TX ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ LTQ_ASC_CLC ; 
 scalar_t__ LTQ_ASC_CON ; 
 scalar_t__ LTQ_ASC_IRNREN ; 
 scalar_t__ LTQ_ASC_PISEL ; 
 scalar_t__ LTQ_ASC_RXFCON ; 
 scalar_t__ LTQ_ASC_TXFCON ; 
 int RXFIFO_FL ; 
 int TXFIFO_FL ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  lqasc_err_int ; 
 int /*<<< orphan*/  lqasc_rx_int ; 
 int /*<<< orphan*/  lqasc_tx_int ; 
 int /*<<< orphan*/  ltq_w32 (int,scalar_t__) ; 
 int /*<<< orphan*/  ltq_w32_mask (int,int,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_port*) ; 
 struct ltq_uart_port* to_ltq_uart_port (struct uart_port*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
lqasc_startup(struct uart_port *port)
{
	struct ltq_uart_port *ltq_port = to_ltq_uart_port(port);
	int retval;

	if (!IS_ERR(ltq_port->clk))
		clk_enable(ltq_port->clk);
	port->uartclk = clk_get_rate(ltq_port->fpiclk);

	ltq_w32_mask(ASCCLC_DISS | ASCCLC_RMCMASK, (1 << ASCCLC_RMCOFFSET),
		port->membase + LTQ_ASC_CLC);

	ltq_w32(0, port->membase + LTQ_ASC_PISEL);
	ltq_w32(
		((TXFIFO_FL << ASCTXFCON_TXFITLOFF) & ASCTXFCON_TXFITLMASK) |
		ASCTXFCON_TXFEN | ASCTXFCON_TXFFLU,
		port->membase + LTQ_ASC_TXFCON);
	ltq_w32(
		((RXFIFO_FL << ASCRXFCON_RXFITLOFF) & ASCRXFCON_RXFITLMASK)
		| ASCRXFCON_RXFEN | ASCRXFCON_RXFFLU,
		port->membase + LTQ_ASC_RXFCON);
	/* make sure other settings are written to hardware before
	 * setting enable bits
	 */
	wmb();
	ltq_w32_mask(0, ASCCON_M_8ASYNC | ASCCON_FEN | ASCCON_TOEN |
		ASCCON_ROEN, port->membase + LTQ_ASC_CON);

	retval = request_irq(ltq_port->tx_irq, lqasc_tx_int,
		0, "asc_tx", port);
	if (retval) {
		pr_err("failed to request lqasc_tx_int\n");
		return retval;
	}

	retval = request_irq(ltq_port->rx_irq, lqasc_rx_int,
		0, "asc_rx", port);
	if (retval) {
		pr_err("failed to request lqasc_rx_int\n");
		goto err1;
	}

	retval = request_irq(ltq_port->err_irq, lqasc_err_int,
		0, "asc_err", port);
	if (retval) {
		pr_err("failed to request lqasc_err_int\n");
		goto err2;
	}

	ltq_w32(ASC_IRNREN_RX | ASC_IRNREN_ERR | ASC_IRNREN_TX,
		port->membase + LTQ_ASC_IRNREN);
	return 0;

err2:
	free_irq(ltq_port->rx_irq, port);
err1:
	free_irq(ltq_port->tx_irq, port);
	return retval;
}