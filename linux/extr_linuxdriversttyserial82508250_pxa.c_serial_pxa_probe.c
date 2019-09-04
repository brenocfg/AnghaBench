#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int line; int regshift; int fifosize; int flags; struct pxa8250_data* private_data; int /*<<< orphan*/  pm; int /*<<< orphan*/  uartclk; TYPE_2__* dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  iotype; int /*<<< orphan*/  type; } ;
struct uart_8250_port {int /*<<< orphan*/  dl_write; TYPE_1__ port; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct pxa8250_data {int line; int /*<<< orphan*/  clk; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_XSCALE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int UPF_IOREMAP ; 
 int UPF_SKIP_TEST ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct pxa8250_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pxa8250_data*) ; 
 int serial8250_register_8250_port (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial_pxa_dl_write ; 
 int /*<<< orphan*/  serial_pxa_pm ; 

__attribute__((used)) static int serial_pxa_probe(struct platform_device *pdev)
{
	struct uart_8250_port uart = {};
	struct pxa8250_data *data;
	struct resource *mmres, *irqres;
	int ret;

	mmres = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	irqres = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!mmres || !irqres)
		return -ENODEV;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(data->clk))
		return PTR_ERR(data->clk);

	ret = clk_prepare(data->clk);
	if (ret)
		return ret;

	ret = of_alias_get_id(pdev->dev.of_node, "serial");
	if (ret >= 0)
		uart.port.line = ret;

	uart.port.type = PORT_XSCALE;
	uart.port.iotype = UPIO_MEM32;
	uart.port.mapbase = mmres->start;
	uart.port.regshift = 2;
	uart.port.irq = irqres->start;
	uart.port.fifosize = 64;
	uart.port.flags = UPF_IOREMAP | UPF_SKIP_TEST;
	uart.port.dev = &pdev->dev;
	uart.port.uartclk = clk_get_rate(data->clk);
	uart.port.pm = serial_pxa_pm;
	uart.port.private_data = data;
	uart.dl_write = serial_pxa_dl_write;

	ret = serial8250_register_8250_port(&uart);
	if (ret < 0)
		goto err_clk;

	data->line = ret;

	platform_set_drvdata(pdev, data);

	return 0;

 err_clk:
	clk_unprepare(data->clk);
	return ret;
}