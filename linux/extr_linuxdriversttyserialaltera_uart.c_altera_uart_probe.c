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
struct uart_port {scalar_t__ mapbase; scalar_t__ irq; int line; TYPE_1__* dev; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  iotype; int /*<<< orphan*/  type; scalar_t__ regshift; int /*<<< orphan*/  membase; int /*<<< orphan*/  uartclk; } ;
struct resource {scalar_t__ start; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {int id; TYPE_1__ dev; } ;
struct altera_uart_platform_uart {scalar_t__ mapbase; scalar_t__ irq; scalar_t__ bus_shift; int /*<<< orphan*/  uartclk; } ;
struct TYPE_4__ {struct uart_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_UART_SIZE ; 
 int CONFIG_SERIAL_ALTERA_UART_MAXPORTS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  PORT_ALTERA_UART ; 
 int /*<<< orphan*/  SERIAL_IO_MEM ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  altera_uart_driver ; 
 int /*<<< orphan*/  altera_uart_ops ; 
 TYPE_2__* altera_uart_ports ; 
 struct altera_uart_platform_uart* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uart_port*) ; 
 int /*<<< orphan*/  uart_add_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int altera_uart_probe(struct platform_device *pdev)
{
	struct altera_uart_platform_uart *platp = dev_get_platdata(&pdev->dev);
	struct uart_port *port;
	struct resource *res_mem;
	struct resource *res_irq;
	int i = pdev->id;
	int ret;

	/* if id is -1 scan for a free id and use that one */
	if (i == -1) {
		for (i = 0; i < CONFIG_SERIAL_ALTERA_UART_MAXPORTS; i++)
			if (altera_uart_ports[i].port.mapbase == 0)
				break;
	}

	if (i < 0 || i >= CONFIG_SERIAL_ALTERA_UART_MAXPORTS)
		return -EINVAL;

	port = &altera_uart_ports[i].port;

	res_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res_mem)
		port->mapbase = res_mem->start;
	else if (platp)
		port->mapbase = platp->mapbase;
	else
		return -EINVAL;

	res_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res_irq)
		port->irq = res_irq->start;
	else if (platp)
		port->irq = platp->irq;

	/* Check platform data first so we can override device node data */
	if (platp)
		port->uartclk = platp->uartclk;
	else {
		ret = of_property_read_u32(pdev->dev.of_node, "clock-frequency",
					   &port->uartclk);
		if (ret)
			return ret;
	}

	port->membase = ioremap(port->mapbase, ALTERA_UART_SIZE);
	if (!port->membase)
		return -ENOMEM;

	if (platp)
		port->regshift = platp->bus_shift;
	else
		port->regshift = 0;

	port->line = i;
	port->type = PORT_ALTERA_UART;
	port->iotype = SERIAL_IO_MEM;
	port->ops = &altera_uart_ops;
	port->flags = UPF_BOOT_AUTOCONF;
	port->dev = &pdev->dev;

	platform_set_drvdata(pdev, port);

	uart_add_one_port(&altera_uart_driver, port);

	return 0;
}