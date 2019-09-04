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
struct uart_port {int line; int irq; int /*<<< orphan*/  membase; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  fifosize; int /*<<< orphan*/  iotype; int /*<<< orphan*/  type; int /*<<< orphan*/ * dev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;
struct TYPE_4__ {struct uart_port port; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__**) ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct clk*) ; 
 int /*<<< orphan*/  PORT_SPRD ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRD_DEF_RATE ; 
 int /*<<< orphan*/  SPRD_FIFO_SIZE ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 TYPE_1__* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uart_port*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  serial_sprd_ops ; 
 TYPE_1__** sprd_port ; 
 int /*<<< orphan*/  sprd_ports_num ; 
 int sprd_probe_dt_alias (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprd_remove (struct platform_device*) ; 
 int /*<<< orphan*/  sprd_uart_driver ; 
 int uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 
 int uart_register_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sprd_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct uart_port *up;
	struct clk *clk;
	int irq;
	int index;
	int ret;

	for (index = 0; index < ARRAY_SIZE(sprd_port); index++)
		if (sprd_port[index] == NULL)
			break;

	if (index == ARRAY_SIZE(sprd_port))
		return -EBUSY;

	index = sprd_probe_dt_alias(index, &pdev->dev);

	sprd_port[index] = devm_kzalloc(&pdev->dev,
		sizeof(*sprd_port[index]), GFP_KERNEL);
	if (!sprd_port[index])
		return -ENOMEM;

	up = &sprd_port[index]->port;
	up->dev = &pdev->dev;
	up->line = index;
	up->type = PORT_SPRD;
	up->iotype = UPIO_MEM;
	up->uartclk = SPRD_DEF_RATE;
	up->fifosize = SPRD_FIFO_SIZE;
	up->ops = &serial_sprd_ops;
	up->flags = UPF_BOOT_AUTOCONF;

	clk = devm_clk_get(&pdev->dev, NULL);
	if (!IS_ERR_OR_NULL(clk))
		up->uartclk = clk_get_rate(clk);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "not provide mem resource\n");
		return -ENODEV;
	}
	up->mapbase = res->start;
	up->membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(up->membase))
		return PTR_ERR(up->membase);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "not provide irq resource: %d\n", irq);
		return irq;
	}
	up->irq = irq;

	if (!sprd_ports_num) {
		ret = uart_register_driver(&sprd_uart_driver);
		if (ret < 0) {
			pr_err("Failed to register SPRD-UART driver\n");
			return ret;
		}
	}
	sprd_ports_num++;

	ret = uart_add_one_port(&sprd_uart_driver, up);
	if (ret) {
		sprd_port[index] = NULL;
		sprd_remove(pdev);
	}

	platform_set_drvdata(pdev, up);

	return ret;
}