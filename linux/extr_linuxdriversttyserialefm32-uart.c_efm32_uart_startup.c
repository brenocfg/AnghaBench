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
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  uartclk; } ;
struct TYPE_2__ {int /*<<< orphan*/  location; } ;
struct efm32_uart_port {int /*<<< orphan*/  clk; int /*<<< orphan*/  txirq; TYPE_1__ pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  UARTn_CMD ; 
 int UARTn_CMD_RXEN ; 
 int /*<<< orphan*/  UARTn_IEN ; 
 int UARTn_IF_RXDATAV ; 
 int UARTn_IF_RXOF ; 
 int /*<<< orphan*/  UARTn_ROUTE ; 
 int UARTn_ROUTE_LOCATION (int /*<<< orphan*/ ) ; 
 int UARTn_ROUTE_RXPEN ; 
 int UARTn_ROUTE_TXPEN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm32_uart_rxirq ; 
 int /*<<< orphan*/  efm32_uart_txirq ; 
 int /*<<< orphan*/  efm32_uart_write32 (struct efm32_uart_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm_debug (struct efm32_uart_port*,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct efm32_uart_port*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct efm32_uart_port*) ; 
 struct efm32_uart_port* to_efm_port (struct uart_port*) ; 

__attribute__((used)) static int efm32_uart_startup(struct uart_port *port)
{
	struct efm32_uart_port *efm_port = to_efm_port(port);
	int ret;

	ret = clk_enable(efm_port->clk);
	if (ret) {
		efm_debug(efm_port, "failed to enable clk\n");
		goto err_clk_enable;
	}
	port->uartclk = clk_get_rate(efm_port->clk);

	/* Enable pins at configured location */
	efm32_uart_write32(efm_port,
			UARTn_ROUTE_LOCATION(efm_port->pdata.location) |
			UARTn_ROUTE_RXPEN | UARTn_ROUTE_TXPEN,
			UARTn_ROUTE);

	ret = request_irq(port->irq, efm32_uart_rxirq, 0,
			DRIVER_NAME, efm_port);
	if (ret) {
		efm_debug(efm_port, "failed to register rxirq\n");
		goto err_request_irq_rx;
	}

	/* disable all irqs */
	efm32_uart_write32(efm_port, 0, UARTn_IEN);

	ret = request_irq(efm_port->txirq, efm32_uart_txirq, 0,
			DRIVER_NAME, efm_port);
	if (ret) {
		efm_debug(efm_port, "failed to register txirq\n");
		free_irq(port->irq, efm_port);
err_request_irq_rx:

		clk_disable(efm_port->clk);
	} else {
		efm32_uart_write32(efm_port,
				UARTn_IF_RXDATAV | UARTn_IF_RXOF, UARTn_IEN);
		efm32_uart_write32(efm_port, UARTn_CMD_RXEN, UARTn_CMD);
	}

err_clk_enable:
	return ret;
}