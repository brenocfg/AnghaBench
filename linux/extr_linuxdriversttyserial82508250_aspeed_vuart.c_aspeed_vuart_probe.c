#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int mapbase; int custom_divisor; int regshift; int fifosize; int line; int uartclk; int flags; int /*<<< orphan*/  irq; int /*<<< orphan*/  type; int /*<<< orphan*/  iotype; int /*<<< orphan*/  handle_irq; int /*<<< orphan*/  irqflags; TYPE_2__* dev; int /*<<< orphan*/  status; int /*<<< orphan*/  unthrottle; int /*<<< orphan*/  throttle; int /*<<< orphan*/  shutdown; int /*<<< orphan*/  startup; int /*<<< orphan*/  mapsize; int /*<<< orphan*/  membase; struct aspeed_vuart* private_data; } ;
struct uart_8250_port {TYPE_1__ port; int /*<<< orphan*/  capabilities; } ;
struct resource {int start; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct aspeed_vuart {int line; TYPE_2__* dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; int /*<<< orphan*/  unthrottle_timer; } ;
typedef  int /*<<< orphan*/  port ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_16550A ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_CAP_AFE ; 
 int /*<<< orphan*/  UART_CAP_FIFO ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_FIXED_PORT ; 
 int UPF_FIXED_TYPE ; 
 int UPF_NO_THRE_TEST ; 
 int UPF_SHARE_IRQ ; 
 int UPF_SKIP_TEST ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  UPSTAT_SYNC_FIFO ; 
 int /*<<< orphan*/  aspeed_vuart_attr_group ; 
 int /*<<< orphan*/  aspeed_vuart_handle_irq ; 
 int /*<<< orphan*/  aspeed_vuart_set_enabled (struct aspeed_vuart*,int) ; 
 int /*<<< orphan*/  aspeed_vuart_set_host_tx_discard (struct aspeed_vuart*,int) ; 
 int /*<<< orphan*/  aspeed_vuart_shutdown ; 
 int /*<<< orphan*/  aspeed_vuart_startup ; 
 int /*<<< orphan*/  aspeed_vuart_throttle ; 
 int /*<<< orphan*/  aspeed_vuart_unthrottle ; 
 int /*<<< orphan*/  aspeed_vuart_unthrottle_exp ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct aspeed_vuart* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct aspeed_vuart*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int serial8250_register_8250_port (struct uart_8250_port*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aspeed_vuart_probe(struct platform_device *pdev)
{
	struct uart_8250_port port;
	struct aspeed_vuart *vuart;
	struct device_node *np;
	struct resource *res;
	u32 clk, prop;
	int rc;

	np = pdev->dev.of_node;

	vuart = devm_kzalloc(&pdev->dev, sizeof(*vuart), GFP_KERNEL);
	if (!vuart)
		return -ENOMEM;

	vuart->dev = &pdev->dev;
	timer_setup(&vuart->unthrottle_timer, aspeed_vuart_unthrottle_exp, 0);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	vuart->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(vuart->regs))
		return PTR_ERR(vuart->regs);

	memset(&port, 0, sizeof(port));
	port.port.private_data = vuart;
	port.port.membase = vuart->regs;
	port.port.mapbase = res->start;
	port.port.mapsize = resource_size(res);
	port.port.startup = aspeed_vuart_startup;
	port.port.shutdown = aspeed_vuart_shutdown;
	port.port.throttle = aspeed_vuart_throttle;
	port.port.unthrottle = aspeed_vuart_unthrottle;
	port.port.status = UPSTAT_SYNC_FIFO;
	port.port.dev = &pdev->dev;

	rc = sysfs_create_group(&vuart->dev->kobj, &aspeed_vuart_attr_group);
	if (rc < 0)
		return rc;

	if (of_property_read_u32(np, "clock-frequency", &clk)) {
		vuart->clk = devm_clk_get(&pdev->dev, NULL);
		if (IS_ERR(vuart->clk)) {
			dev_warn(&pdev->dev,
				"clk or clock-frequency not defined\n");
			rc = PTR_ERR(vuart->clk);
			goto err_sysfs_remove;
		}

		rc = clk_prepare_enable(vuart->clk);
		if (rc < 0)
			goto err_sysfs_remove;

		clk = clk_get_rate(vuart->clk);
	}

	/* If current-speed was set, then try not to change it. */
	if (of_property_read_u32(np, "current-speed", &prop) == 0)
		port.port.custom_divisor = clk / (16 * prop);

	/* Check for shifted address mapping */
	if (of_property_read_u32(np, "reg-offset", &prop) == 0)
		port.port.mapbase += prop;

	/* Check for registers offset within the devices address range */
	if (of_property_read_u32(np, "reg-shift", &prop) == 0)
		port.port.regshift = prop;

	/* Check for fifo size */
	if (of_property_read_u32(np, "fifo-size", &prop) == 0)
		port.port.fifosize = prop;

	/* Check for a fixed line number */
	rc = of_alias_get_id(np, "serial");
	if (rc >= 0)
		port.port.line = rc;

	port.port.irq = irq_of_parse_and_map(np, 0);
	port.port.irqflags = IRQF_SHARED;
	port.port.handle_irq = aspeed_vuart_handle_irq;
	port.port.iotype = UPIO_MEM;
	port.port.type = PORT_16550A;
	port.port.uartclk = clk;
	port.port.flags = UPF_SHARE_IRQ | UPF_BOOT_AUTOCONF
		| UPF_FIXED_PORT | UPF_FIXED_TYPE | UPF_NO_THRE_TEST;

	if (of_property_read_bool(np, "no-loopback-test"))
		port.port.flags |= UPF_SKIP_TEST;

	if (port.port.fifosize)
		port.capabilities = UART_CAP_FIFO;

	if (of_property_read_bool(np, "auto-flow-control"))
		port.capabilities |= UART_CAP_AFE;

	rc = serial8250_register_8250_port(&port);
	if (rc < 0)
		goto err_clk_disable;

	vuart->line = rc;

	aspeed_vuart_set_enabled(vuart, true);
	aspeed_vuart_set_host_tx_discard(vuart, true);
	platform_set_drvdata(pdev, vuart);

	return 0;

err_clk_disable:
	clk_disable_unprepare(vuart->clk);
	irq_dispose_mapping(port.port.irq);
err_sysfs_remove:
	sysfs_remove_group(&vuart->dev->kobj, &aspeed_vuart_attr_group);
	return rc;
}