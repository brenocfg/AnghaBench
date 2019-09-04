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
struct TYPE_2__ {scalar_t__ has_wakeup; } ;
struct stm32_usart_info {TYPE_1__ cfg; } ;
struct stm32_port {scalar_t__ wakeirq; int /*<<< orphan*/  clk; struct stm32_usart_info* info; int /*<<< orphan*/  port; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int stm32_init_port (struct stm32_port*,struct platform_device*) ; 
 int /*<<< orphan*/  stm32_match ; 
 int stm32_of_dma_rx_probe (struct stm32_port*,struct platform_device*) ; 
 int stm32_of_dma_tx_probe (struct stm32_port*,struct platform_device*) ; 
 struct stm32_port* stm32_of_get_stm32_port (struct platform_device*) ; 
 int /*<<< orphan*/  stm32_usart_driver ; 
 int uart_add_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32_serial_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct stm32_port *stm32port;
	int ret;

	stm32port = stm32_of_get_stm32_port(pdev);
	if (!stm32port)
		return -ENODEV;

	match = of_match_device(stm32_match, &pdev->dev);
	if (match && match->data)
		stm32port->info = (struct stm32_usart_info *)match->data;
	else
		return -EINVAL;

	ret = stm32_init_port(stm32port, pdev);
	if (ret)
		return ret;

	if (stm32port->info->cfg.has_wakeup && stm32port->wakeirq >= 0) {
		ret = device_init_wakeup(&pdev->dev, true);
		if (ret)
			goto err_uninit;
	}

	ret = uart_add_one_port(&stm32_usart_driver, &stm32port->port);
	if (ret)
		goto err_nowup;

	ret = stm32_of_dma_rx_probe(stm32port, pdev);
	if (ret)
		dev_info(&pdev->dev, "interrupt mode used for rx (no dma)\n");

	ret = stm32_of_dma_tx_probe(stm32port, pdev);
	if (ret)
		dev_info(&pdev->dev, "interrupt mode used for tx (no dma)\n");

	platform_set_drvdata(pdev, &stm32port->port);

	return 0;

err_nowup:
	if (stm32port->info->cfg.has_wakeup && stm32port->wakeirq >= 0)
		device_init_wakeup(&pdev->dev, false);

err_uninit:
	clk_disable_unprepare(stm32port->clk);

	return ret;
}