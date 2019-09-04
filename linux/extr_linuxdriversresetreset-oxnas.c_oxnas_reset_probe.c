#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_6__ {int nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct oxnas_reset {TYPE_2__ rcdev; int /*<<< orphan*/  regmap; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct oxnas_reset* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  oxnas_reset_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct oxnas_reset*) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oxnas_reset_probe(struct platform_device *pdev)
{
	struct oxnas_reset *data;
	struct device *parent;

	parent = pdev->dev.parent;
	if (!parent) {
		dev_err(&pdev->dev, "no parent\n");
		return -ENODEV;
	}

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->regmap = syscon_node_to_regmap(parent->of_node);
	if (IS_ERR(data->regmap)) {
		dev_err(&pdev->dev, "failed to get parent regmap\n");
		return PTR_ERR(data->regmap);
	}

	platform_set_drvdata(pdev, data);

	data->rcdev.owner = THIS_MODULE;
	data->rcdev.nr_resets = 32;
	data->rcdev.ops = &oxnas_reset_ops;
	data->rcdev.of_node = pdev->dev.of_node;

	return devm_reset_controller_register(&pdev->dev, &data->rcdev);
}