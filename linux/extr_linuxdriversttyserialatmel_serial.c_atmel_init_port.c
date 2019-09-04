#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
struct uart_port {int flags; int fifosize; TYPE_2__ rs485; int /*<<< orphan*/  uartclk; int /*<<< orphan*/ * membase; int /*<<< orphan*/  rs485_config; int /*<<< orphan*/  irq; int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  iotype; } ;
struct platform_device {int /*<<< orphan*/  dev; TYPE_1__* resource; } ;
struct atmel_uart_port {int tx_done_mask; int /*<<< orphan*/ * clk; int /*<<< orphan*/  rx_ring; struct uart_port uart; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int ATMEL_US_ENDTX ; 
 int ATMEL_US_TXBUFE ; 
 int ATMEL_US_TXEMPTY ; 
 int ATMEL_US_TXRDY ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PDC_BUFFER_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int SER_RS485_ENABLED ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_IOREMAP ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  atmel_config_rs485 ; 
 int /*<<< orphan*/  atmel_init_property (struct atmel_uart_port*,struct platform_device*) ; 
 int /*<<< orphan*/  atmel_pops ; 
 int /*<<< orphan*/  atmel_set_ops (struct uart_port*) ; 
 scalar_t__ atmel_use_pdc_tx (struct uart_port*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_get_rs485_mode (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int atmel_init_port(struct atmel_uart_port *atmel_port,
				      struct platform_device *pdev)
{
	int ret;
	struct uart_port *port = &atmel_port->uart;

	atmel_init_property(atmel_port, pdev);
	atmel_set_ops(port);

	uart_get_rs485_mode(&pdev->dev, &port->rs485);

	port->iotype		= UPIO_MEM;
	port->flags		= UPF_BOOT_AUTOCONF | UPF_IOREMAP;
	port->ops		= &atmel_pops;
	port->fifosize		= 1;
	port->dev		= &pdev->dev;
	port->mapbase	= pdev->resource[0].start;
	port->irq	= pdev->resource[1].start;
	port->rs485_config	= atmel_config_rs485;
	port->membase	= NULL;

	memset(&atmel_port->rx_ring, 0, sizeof(atmel_port->rx_ring));

	/* for console, the clock could already be configured */
	if (!atmel_port->clk) {
		atmel_port->clk = clk_get(&pdev->dev, "usart");
		if (IS_ERR(atmel_port->clk)) {
			ret = PTR_ERR(atmel_port->clk);
			atmel_port->clk = NULL;
			return ret;
		}
		ret = clk_prepare_enable(atmel_port->clk);
		if (ret) {
			clk_put(atmel_port->clk);
			atmel_port->clk = NULL;
			return ret;
		}
		port->uartclk = clk_get_rate(atmel_port->clk);
		clk_disable_unprepare(atmel_port->clk);
		/* only enable clock when USART is in use */
	}

	/* Use TXEMPTY for interrupt when rs485 else TXRDY or ENDTX|TXBUFE */
	if (port->rs485.flags & SER_RS485_ENABLED)
		atmel_port->tx_done_mask = ATMEL_US_TXEMPTY;
	else if (atmel_use_pdc_tx(port)) {
		port->fifosize = PDC_BUFFER_SIZE;
		atmel_port->tx_done_mask = ATMEL_US_ENDTX | ATMEL_US_TXBUFE;
	} else {
		atmel_port->tx_done_mask = ATMEL_US_TXRDY;
	}

	return 0;
}