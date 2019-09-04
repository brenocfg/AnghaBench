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
struct uartlite_data {int /*<<< orphan*/ * clk; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int clk_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct uartlite_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ulite_assign (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,struct uartlite_data*) ; 

__attribute__((used)) static int ulite_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct uartlite_data *pdata;
	int irq, ret;
	int id = pdev->id;
#ifdef CONFIG_OF
	const __be32 *prop;

	prop = of_get_property(pdev->dev.of_node, "port-number", NULL);
	if (prop)
		id = be32_to_cpup(prop);
#endif
	pdata = devm_kzalloc(&pdev->dev, sizeof(struct uartlite_data),
			     GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return -ENXIO;

	pdata->clk = devm_clk_get(&pdev->dev, "s_axi_aclk");
	if (IS_ERR(pdata->clk)) {
		if (PTR_ERR(pdata->clk) != -ENOENT)
			return PTR_ERR(pdata->clk);

		/*
		 * Clock framework support is optional, continue on
		 * anyways if we don't find a matching clock.
		 */
		pdata->clk = NULL;
	}

	ret = clk_prepare(pdata->clk);
	if (ret) {
		dev_err(&pdev->dev, "Failed to prepare clock\n");
		return ret;
	}

	return ulite_assign(&pdev->dev, id, res->start, irq, pdata);
}