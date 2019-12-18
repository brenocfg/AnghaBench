#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct switch_dev {char* name; char* alias; int /*<<< orphan*/ * ops; int /*<<< orphan*/  vlans; int /*<<< orphan*/  ports; int /*<<< orphan*/  cpu_port; struct device_node* of_node; } ;
struct rt305x_esw {int port_map; int port_disable; int reg_initval_fct2; int reg_initval_fpa2; int reg_led_polarity; int /*<<< orphan*/  irq; struct switch_dev swdev; int /*<<< orphan*/  reg_rw_lock; int /*<<< orphan*/  base; TYPE_1__* dev; } ;
struct resource {int dummy; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT305X_ESW_NUM_PORTS ; 
 int /*<<< orphan*/  RT305X_ESW_NUM_VIDS ; 
 int /*<<< orphan*/  RT305X_ESW_PORT6 ; 
 int /*<<< orphan*/  RT305X_ESW_PORT_ST_CHG ; 
 int /*<<< orphan*/  RT305X_ESW_REG_IMR ; 
 int /*<<< orphan*/  RT305X_ESW_REG_ISR ; 
 int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct rt305x_esw* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct rt305x_esw*) ; 
 int /*<<< orphan*/  esw_hw_init (struct rt305x_esw*) ; 
 int /*<<< orphan*/  esw_interrupt ; 
 int /*<<< orphan*/  esw_ops ; 
 int /*<<< orphan*/  esw_w32 (struct rt305x_esw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rt305x_esw*) ; 
 int register_switch (struct switch_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_switch (struct switch_dev*) ; 

__attribute__((used)) static int esw_probe(struct platform_device *pdev)
{
	struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	struct device_node *np = pdev->dev.of_node;
	const __be32 *port_map, *port_disable, *reg_init;
	struct switch_dev *swdev;
	struct rt305x_esw *esw;
	int ret;

	esw = devm_kzalloc(&pdev->dev, sizeof(*esw), GFP_KERNEL);
	if (!esw)
		return -ENOMEM;

	esw->dev = &pdev->dev;
	esw->irq = irq_of_parse_and_map(np, 0);
	esw->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(esw->base))
		return PTR_ERR(esw->base);

	port_map = of_get_property(np, "mediatek,portmap", NULL);
	if (port_map)
		esw->port_map = be32_to_cpu(*port_map);

	port_disable = of_get_property(np, "mediatek,portdisable", NULL);
	if (port_disable)
		esw->port_disable = be32_to_cpu(*port_disable);

	reg_init = of_get_property(np, "ralink,fct2", NULL);
	if (reg_init)
		esw->reg_initval_fct2 = be32_to_cpu(*reg_init);

	reg_init = of_get_property(np, "ralink,fpa2", NULL);
	if (reg_init)
		esw->reg_initval_fpa2 = be32_to_cpu(*reg_init);

	reg_init = of_get_property(np, "mediatek,led_polarity", NULL);
	if (reg_init)
		esw->reg_led_polarity = be32_to_cpu(*reg_init);

	swdev = &esw->swdev;
	swdev->of_node = pdev->dev.of_node;
	swdev->name = "rt305x-esw";
	swdev->alias = "rt305x";
	swdev->cpu_port = RT305X_ESW_PORT6;
	swdev->ports = RT305X_ESW_NUM_PORTS;
	swdev->vlans = RT305X_ESW_NUM_VIDS;
	swdev->ops = &esw_ops;

	ret = register_switch(swdev, NULL);
	if (ret < 0) {
		dev_err(&pdev->dev, "register_switch failed\n");
		return ret;
	}

	platform_set_drvdata(pdev, esw);

	spin_lock_init(&esw->reg_rw_lock);

	esw_hw_init(esw);

	reg_init = of_get_property(np, "ralink,rgmii", NULL);
	if (reg_init && be32_to_cpu(*reg_init) == 1) {
		/* 
		 * External switch connected to RGMII interface. 
		 * Unregister the switch device after initialization. 
		 */
		dev_err(&pdev->dev, "RGMII mode, not exporting switch device.\n");
		unregister_switch(&esw->swdev);
		platform_set_drvdata(pdev, NULL);
		return -ENODEV;
	}

	ret = devm_request_irq(&pdev->dev, esw->irq, esw_interrupt, 0, "esw",
			       esw);

	if (!ret) {
		esw_w32(esw, RT305X_ESW_PORT_ST_CHG, RT305X_ESW_REG_ISR);
		esw_w32(esw, ~RT305X_ESW_PORT_ST_CHG, RT305X_ESW_REG_IMR);
	}

	return ret;
}