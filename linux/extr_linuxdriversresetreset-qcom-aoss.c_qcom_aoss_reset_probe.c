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
struct TYPE_2__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  nr_resets; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct qcom_aoss_reset_data {TYPE_1__ rcdev; int /*<<< orphan*/  base; struct qcom_aoss_desc const* desc; } ;
struct qcom_aoss_desc {int /*<<< orphan*/  num_resets; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct qcom_aoss_reset_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (struct device*,TYPE_1__*) ; 
 struct qcom_aoss_desc* of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_aoss_reset_ops ; 

__attribute__((used)) static int qcom_aoss_reset_probe(struct platform_device *pdev)
{
	struct qcom_aoss_reset_data *data;
	struct device *dev = &pdev->dev;
	const struct qcom_aoss_desc *desc;
	struct resource *res;

	desc = of_device_get_match_data(dev);
	if (!desc)
		return -EINVAL;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->desc = desc;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(data->base))
		return PTR_ERR(data->base);

	data->rcdev.owner = THIS_MODULE;
	data->rcdev.ops = &qcom_aoss_reset_ops;
	data->rcdev.nr_resets = desc->num_resets;
	data->rcdev.of_node = dev->of_node;

	return devm_reset_controller_register(dev, &data->rcdev);
}