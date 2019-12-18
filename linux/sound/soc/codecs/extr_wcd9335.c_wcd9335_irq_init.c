#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wcd9335_codec {int intr1; TYPE_1__* dev; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int devm_regmap_add_irq_chip (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int of_irq_get_byname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcd9335_regmap_irq1_chip ; 

__attribute__((used)) static int wcd9335_irq_init(struct wcd9335_codec *wcd)
{
	int ret;

	/*
	 * INTR1 consists of all possible interrupt sources Ear OCP,
	 * HPH OCP, MBHC, MAD, VBAT, and SVA
	 * INTR2 is a subset of first interrupt sources MAD, VBAT, and SVA
	 */
	wcd->intr1 = of_irq_get_byname(wcd->dev->of_node, "intr1");
	if (wcd->intr1 < 0) {
		if (wcd->intr1 != -EPROBE_DEFER)
			dev_err(wcd->dev, "Unable to configure IRQ\n");

		return wcd->intr1;
	}

	ret = devm_regmap_add_irq_chip(wcd->dev, wcd->regmap, wcd->intr1,
				 IRQF_TRIGGER_HIGH, 0,
				 &wcd9335_regmap_irq1_chip, &wcd->irq_data);
	if (ret)
		dev_err(wcd->dev, "Failed to register IRQ chip: %d\n", ret);

	return ret;
}