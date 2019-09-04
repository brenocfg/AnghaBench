#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int uartclk; int irq; int /*<<< orphan*/  mapbase; TYPE_1__* dev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_4__ {scalar_t__ of_node; } ;
struct platform_device {int id; TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct msm_port {unsigned long is_uartdm; void* clk; void* pclk; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int UART_NR ; 
 struct msm_port* UART_TO_MSM (struct uart_port*) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int clk_get_rate (void*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 struct uart_port* msm_get_port_from_line (int) ; 
 int /*<<< orphan*/  msm_uart_driver ; 
 int /*<<< orphan*/  msm_uart_next_id ; 
 int /*<<< orphan*/  msm_uartdm_table ; 
 int of_alias_get_id (scalar_t__,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uart_port*) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int msm_serial_probe(struct platform_device *pdev)
{
	struct msm_port *msm_port;
	struct resource *resource;
	struct uart_port *port;
	const struct of_device_id *id;
	int irq, line;

	if (pdev->dev.of_node)
		line = of_alias_get_id(pdev->dev.of_node, "serial");
	else
		line = pdev->id;

	if (line < 0)
		line = atomic_inc_return(&msm_uart_next_id) - 1;

	if (unlikely(line < 0 || line >= UART_NR))
		return -ENXIO;

	dev_info(&pdev->dev, "msm_serial: detected port #%d\n", line);

	port = msm_get_port_from_line(line);
	port->dev = &pdev->dev;
	msm_port = UART_TO_MSM(port);

	id = of_match_device(msm_uartdm_table, &pdev->dev);
	if (id)
		msm_port->is_uartdm = (unsigned long)id->data;
	else
		msm_port->is_uartdm = 0;

	msm_port->clk = devm_clk_get(&pdev->dev, "core");
	if (IS_ERR(msm_port->clk))
		return PTR_ERR(msm_port->clk);

	if (msm_port->is_uartdm) {
		msm_port->pclk = devm_clk_get(&pdev->dev, "iface");
		if (IS_ERR(msm_port->pclk))
			return PTR_ERR(msm_port->pclk);
	}

	port->uartclk = clk_get_rate(msm_port->clk);
	dev_info(&pdev->dev, "uartclk = %d\n", port->uartclk);

	resource = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (unlikely(!resource))
		return -ENXIO;
	port->mapbase = resource->start;

	irq = platform_get_irq(pdev, 0);
	if (unlikely(irq < 0))
		return -ENXIO;
	port->irq = irq;

	platform_set_drvdata(pdev, port);

	return uart_add_one_port(&msm_uart_driver, port);
}