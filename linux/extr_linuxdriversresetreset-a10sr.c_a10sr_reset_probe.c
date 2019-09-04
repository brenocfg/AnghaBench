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
struct TYPE_4__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct altr_a10sr {int /*<<< orphan*/  regmap; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  nr_resets; int /*<<< orphan*/  owner; } ;
struct a10sr_reset {TYPE_2__ rcdev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  A10SR_RESET_NUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  a10sr_reset_ops ; 
 struct altr_a10sr* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct a10sr_reset* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct a10sr_reset*) ; 

__attribute__((used)) static int a10sr_reset_probe(struct platform_device *pdev)
{
	struct altr_a10sr *a10sr = dev_get_drvdata(pdev->dev.parent);
	struct a10sr_reset *a10r;

	a10r = devm_kzalloc(&pdev->dev, sizeof(struct a10sr_reset),
			    GFP_KERNEL);
	if (!a10r)
		return -ENOMEM;

	a10r->rcdev.owner = THIS_MODULE;
	a10r->rcdev.nr_resets = A10SR_RESET_NUM;
	a10r->rcdev.ops = &a10sr_reset_ops;
	a10r->rcdev.of_node = pdev->dev.of_node;
	a10r->regmap = a10sr->regmap;

	platform_set_drvdata(pdev, a10r);

	return devm_reset_controller_register(&pdev->dev, &a10r->rcdev);
}