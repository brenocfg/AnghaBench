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
struct tps62360_regulator_platform_data {int vsel0_def_state; int vsel1_def_state; int en_internal_pulldn; int en_discharge; void* vsel1_gpio; void* vsel0_gpio; int /*<<< orphan*/  reg_init_data; } ;
struct regulator_desc {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct tps62360_regulator_platform_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 void* of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_regulator_init_data (struct device*,struct device_node*,struct regulator_desc const*) ; 

__attribute__((used)) static struct tps62360_regulator_platform_data *
	of_get_tps62360_platform_data(struct device *dev,
				      const struct regulator_desc *desc)
{
	struct tps62360_regulator_platform_data *pdata;
	struct device_node *np = dev->of_node;

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;

	pdata->reg_init_data = of_get_regulator_init_data(dev, dev->of_node,
							  desc);
	if (!pdata->reg_init_data) {
		dev_err(dev, "Not able to get OF regulator init data\n");
		return NULL;
	}

	pdata->vsel0_gpio = of_get_named_gpio(np, "vsel0-gpio", 0);
	pdata->vsel1_gpio = of_get_named_gpio(np, "vsel1-gpio", 0);

	if (of_find_property(np, "ti,vsel0-state-high", NULL))
		pdata->vsel0_def_state = 1;

	if (of_find_property(np, "ti,vsel1-state-high", NULL))
		pdata->vsel1_def_state = 1;

	if (of_find_property(np, "ti,enable-pull-down", NULL))
		pdata->en_internal_pulldn = true;

	if (of_find_property(np, "ti,enable-vout-discharge", NULL))
		pdata->en_discharge = true;

	return pdata;
}