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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct hisi_thermal_data {int irq; TYPE_1__ sensor; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; int /*<<< orphan*/  irq_handler; int /*<<< orphan*/  disable_sensor; int /*<<< orphan*/  enable_sensor; int /*<<< orphan*/  get_temp; struct platform_device* pdev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  HI6220_DEFAULT_SENSOR ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  hi6220_thermal_disable_sensor ; 
 int /*<<< orphan*/  hi6220_thermal_enable_sensor ; 
 int /*<<< orphan*/  hi6220_thermal_get_temp ; 
 int /*<<< orphan*/  hi6220_thermal_irq_handler ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi6220_thermal_probe(struct hisi_thermal_data *data)
{
	struct platform_device *pdev = data->pdev;
	struct device *dev = &pdev->dev;
	struct resource *res;
	int ret;

	data->get_temp = hi6220_thermal_get_temp;
	data->enable_sensor = hi6220_thermal_enable_sensor;
	data->disable_sensor = hi6220_thermal_disable_sensor;
	data->irq_handler = hi6220_thermal_irq_handler;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(data->regs)) {
		dev_err(dev, "failed to get io address\n");
		return PTR_ERR(data->regs);
	}

	data->clk = devm_clk_get(dev, "thermal_clk");
	if (IS_ERR(data->clk)) {
		ret = PTR_ERR(data->clk);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get thermal clk: %d\n", ret);
		return ret;
	}

	data->irq = platform_get_irq(pdev, 0);
	if (data->irq < 0)
		return data->irq;

	data->sensor.id = HI6220_DEFAULT_SENSOR;

	return 0;
}