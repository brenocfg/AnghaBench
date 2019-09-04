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
struct uart_port {scalar_t__ mapbase; struct cdns_uart* private_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cdns_uart {int /*<<< orphan*/  pclk; int /*<<< orphan*/  uartclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns_uart_uart_driver ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct uart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int cdns_uart_remove(struct platform_device *pdev)
{
	struct uart_port *port = platform_get_drvdata(pdev);
	struct cdns_uart *cdns_uart_data = port->private_data;
	int rc;

	/* Remove the cdns_uart port from the serial core */
#ifdef CONFIG_COMMON_CLK
	clk_notifier_unregister(cdns_uart_data->uartclk,
			&cdns_uart_data->clk_rate_change_nb);
#endif
	rc = uart_remove_one_port(&cdns_uart_uart_driver, port);
	port->mapbase = 0;
	clk_disable_unprepare(cdns_uart_data->uartclk);
	clk_disable_unprepare(cdns_uart_data->pclk);
	pm_runtime_disable(&pdev->dev);
	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_dont_use_autosuspend(&pdev->dev);
	return rc;
}