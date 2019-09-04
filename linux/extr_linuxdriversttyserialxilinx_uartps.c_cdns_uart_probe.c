#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int irq; int line; struct cdns_uart* private_data; int /*<<< orphan*/  uartclk; TYPE_1__* dev; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  fifosize; int /*<<< orphan*/ * ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  iotype; int /*<<< orphan*/  type; int /*<<< orphan*/ * membase; int /*<<< orphan*/  lock; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {struct cdns_platform_data* data; } ;
struct cdns_uart {void* pclk; void* uartclk; struct uart_port* port; int /*<<< orphan*/  quirks; } ;
struct cdns_platform_data {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_UART_FIFO_SIZE ; 
 int CDNS_UART_NR_PORTS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PORT_UNKNOWN ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  UART_AUTOSUSPEND_TIMEOUT ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int /*<<< orphan*/  cdns_uart_of_match ; 
 int /*<<< orphan*/  cdns_uart_ops ; 
 int /*<<< orphan*/  cdns_uart_uart_driver ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int /*<<< orphan*/  clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 void* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uart_port*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int cdns_uart_probe(struct platform_device *pdev)
{
	int rc, id, irq;
	struct uart_port *port;
	struct resource *res;
	struct cdns_uart *cdns_uart_data;
	const struct of_device_id *match;

	cdns_uart_data = devm_kzalloc(&pdev->dev, sizeof(*cdns_uart_data),
			GFP_KERNEL);
	if (!cdns_uart_data)
		return -ENOMEM;
	port = devm_kzalloc(&pdev->dev, sizeof(*port), GFP_KERNEL);
	if (!port)
		return -ENOMEM;

	match = of_match_node(cdns_uart_of_match, pdev->dev.of_node);
	if (match && match->data) {
		const struct cdns_platform_data *data = match->data;

		cdns_uart_data->quirks = data->quirks;
	}

	cdns_uart_data->pclk = devm_clk_get(&pdev->dev, "pclk");
	if (IS_ERR(cdns_uart_data->pclk)) {
		cdns_uart_data->pclk = devm_clk_get(&pdev->dev, "aper_clk");
		if (!IS_ERR(cdns_uart_data->pclk))
			dev_err(&pdev->dev, "clock name 'aper_clk' is deprecated.\n");
	}
	if (IS_ERR(cdns_uart_data->pclk)) {
		dev_err(&pdev->dev, "pclk clock not found.\n");
		return PTR_ERR(cdns_uart_data->pclk);
	}

	cdns_uart_data->uartclk = devm_clk_get(&pdev->dev, "uart_clk");
	if (IS_ERR(cdns_uart_data->uartclk)) {
		cdns_uart_data->uartclk = devm_clk_get(&pdev->dev, "ref_clk");
		if (!IS_ERR(cdns_uart_data->uartclk))
			dev_err(&pdev->dev, "clock name 'ref_clk' is deprecated.\n");
	}
	if (IS_ERR(cdns_uart_data->uartclk)) {
		dev_err(&pdev->dev, "uart_clk clock not found.\n");
		return PTR_ERR(cdns_uart_data->uartclk);
	}

	rc = clk_prepare_enable(cdns_uart_data->pclk);
	if (rc) {
		dev_err(&pdev->dev, "Unable to enable pclk clock.\n");
		return rc;
	}
	rc = clk_prepare_enable(cdns_uart_data->uartclk);
	if (rc) {
		dev_err(&pdev->dev, "Unable to enable device clock.\n");
		goto err_out_clk_dis_pclk;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		rc = -ENODEV;
		goto err_out_clk_disable;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0) {
		rc = -ENXIO;
		goto err_out_clk_disable;
	}

#ifdef CONFIG_COMMON_CLK
	cdns_uart_data->clk_rate_change_nb.notifier_call =
			cdns_uart_clk_notifier_cb;
	if (clk_notifier_register(cdns_uart_data->uartclk,
				&cdns_uart_data->clk_rate_change_nb))
		dev_warn(&pdev->dev, "Unable to register clock notifier.\n");
#endif
	/* Look for a serialN alias */
	id = of_alias_get_id(pdev->dev.of_node, "serial");
	if (id < 0)
		id = 0;

	if (id >= CDNS_UART_NR_PORTS) {
		dev_err(&pdev->dev, "Cannot get uart_port structure\n");
		rc = -ENODEV;
		goto err_out_notif_unreg;
	}

	/* At this point, we've got an empty uart_port struct, initialize it */
	spin_lock_init(&port->lock);
	port->membase	= NULL;
	port->irq	= 0;
	port->type	= PORT_UNKNOWN;
	port->iotype	= UPIO_MEM32;
	port->flags	= UPF_BOOT_AUTOCONF;
	port->ops	= &cdns_uart_ops;
	port->fifosize	= CDNS_UART_FIFO_SIZE;
	port->line	= id;
	port->dev	= NULL;

	/*
	 * Register the port.
	 * This function also registers this device with the tty layer
	 * and triggers invocation of the config_port() entry point.
	 */
	port->mapbase = res->start;
	port->irq = irq;
	port->dev = &pdev->dev;
	port->uartclk = clk_get_rate(cdns_uart_data->uartclk);
	port->private_data = cdns_uart_data;
	cdns_uart_data->port = port;
	platform_set_drvdata(pdev, port);

	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev, UART_AUTOSUSPEND_TIMEOUT);
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

#ifdef CONFIG_SERIAL_XILINX_PS_UART_CONSOLE
	/*
	 * If console hasn't been found yet try to assign this port
	 * because it is required to be assigned for console setup function.
	 * If register_console() don't assign value, then console_port pointer
	 * is cleanup.
	 */
	if (cdns_uart_uart_driver.cons->index == -1)
		console_port = port;
#endif

	rc = uart_add_one_port(&cdns_uart_uart_driver, port);
	if (rc) {
		dev_err(&pdev->dev,
			"uart_add_one_port() failed; err=%i\n", rc);
		goto err_out_pm_disable;
	}

#ifdef CONFIG_SERIAL_XILINX_PS_UART_CONSOLE
	/* This is not port which is used for console that's why clean it up */
	if (cdns_uart_uart_driver.cons->index == -1)
		console_port = NULL;
#endif

	return 0;

err_out_pm_disable:
	pm_runtime_disable(&pdev->dev);
	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_dont_use_autosuspend(&pdev->dev);
err_out_notif_unreg:
#ifdef CONFIG_COMMON_CLK
	clk_notifier_unregister(cdns_uart_data->uartclk,
			&cdns_uart_data->clk_rate_change_nb);
#endif
err_out_clk_disable:
	clk_disable_unprepare(cdns_uart_data->uartclk);
err_out_clk_dis_pclk:
	clk_disable_unprepare(cdns_uart_data->pclk);

	return rc;
}