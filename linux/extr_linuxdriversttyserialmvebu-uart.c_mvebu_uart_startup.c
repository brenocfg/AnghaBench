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
struct uart_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  irqflags; scalar_t__ membase; } ;
struct mvebu_uart {int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 unsigned int CTRL_BRK_INT ; 
 unsigned int CTRL_RXFIFO_RST ; 
 unsigned int CTRL_RX_RDY_INT (struct uart_port*) ; 
 unsigned int CTRL_TXFIFO_RST ; 
 int STAT_BRK_ERR ; 
 scalar_t__ UART_CTRL (struct uart_port*) ; 
 scalar_t__ UART_INTR (struct uart_port*) ; 
 size_t UART_IRQ_SUM ; 
 size_t UART_RX_IRQ ; 
 scalar_t__ UART_STAT ; 
 size_t UART_TX_IRQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  mvebu_uart_isr ; 
 int /*<<< orphan*/  mvebu_uart_rx_isr ; 
 int /*<<< orphan*/  mvebu_uart_tx_isr ; 
 void* readl (scalar_t__) ; 
 struct mvebu_uart* to_mvuart (struct uart_port*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int mvebu_uart_startup(struct uart_port *port)
{
	struct mvebu_uart *mvuart = to_mvuart(port);
	unsigned int ctl;
	int ret;

	writel(CTRL_TXFIFO_RST | CTRL_RXFIFO_RST,
	       port->membase + UART_CTRL(port));
	udelay(1);

	/* Clear the error bits of state register before IRQ request */
	ret = readl(port->membase + UART_STAT);
	ret |= STAT_BRK_ERR;
	writel(ret, port->membase + UART_STAT);

	writel(CTRL_BRK_INT, port->membase + UART_CTRL(port));

	ctl = readl(port->membase + UART_INTR(port));
	ctl |= CTRL_RX_RDY_INT(port);
	writel(ctl, port->membase + UART_INTR(port));

	if (!mvuart->irq[UART_TX_IRQ]) {
		/* Old bindings with just one interrupt (UART0 only) */
		ret = devm_request_irq(port->dev, mvuart->irq[UART_IRQ_SUM],
				       mvebu_uart_isr, port->irqflags,
				       dev_name(port->dev), port);
		if (ret) {
			dev_err(port->dev, "unable to request IRQ %d\n",
				mvuart->irq[UART_IRQ_SUM]);
			return ret;
		}
	} else {
		/* New bindings with an IRQ for RX and TX (both UART) */
		ret = devm_request_irq(port->dev, mvuart->irq[UART_RX_IRQ],
				       mvebu_uart_rx_isr, port->irqflags,
				       dev_name(port->dev), port);
		if (ret) {
			dev_err(port->dev, "unable to request IRQ %d\n",
				mvuart->irq[UART_RX_IRQ]);
			return ret;
		}

		ret = devm_request_irq(port->dev, mvuart->irq[UART_TX_IRQ],
				       mvebu_uart_tx_isr, port->irqflags,
				       dev_name(port->dev),
				       port);
		if (ret) {
			dev_err(port->dev, "unable to request IRQ %d\n",
				mvuart->irq[UART_TX_IRQ]);
			devm_free_irq(port->dev, mvuart->irq[UART_RX_IRQ],
				      port);
			return ret;
		}
	}

	return 0;
}