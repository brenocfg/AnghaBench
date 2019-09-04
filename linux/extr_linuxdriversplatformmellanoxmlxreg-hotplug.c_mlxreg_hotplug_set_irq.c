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
struct TYPE_4__ {int /*<<< orphan*/  work; } ;
struct mlxreg_hotplug_priv_data {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; TYPE_2__ dwork_irq; int /*<<< orphan*/  regmap; TYPE_1__* pdev; } ;
struct mlxreg_core_item {int /*<<< orphan*/  mask; scalar_t__ reg; int /*<<< orphan*/  cache; scalar_t__ inversed; } ;
struct mlxreg_core_hotplug_platform_data {int counter; int /*<<< orphan*/  mask_low; scalar_t__ cell_low; int /*<<< orphan*/  mask; scalar_t__ cell; struct mlxreg_core_item* items; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MLXREG_HOTPLUG_AGGR_MASK_OFF ; 
 scalar_t__ MLXREG_HOTPLUG_EVENT_OFF ; 
 scalar_t__ MLXREG_HOTPLUG_MASK_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mlxreg_core_hotplug_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxreg_hotplug_work_handler (int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxreg_hotplug_set_irq(struct mlxreg_hotplug_priv_data *priv)
{
	struct mlxreg_core_hotplug_platform_data *pdata;
	struct mlxreg_core_item *item;
	int i, ret;

	pdata = dev_get_platdata(&priv->pdev->dev);
	item = pdata->items;

	for (i = 0; i < pdata->counter; i++, item++) {
		/* Clear group presense event. */
		ret = regmap_write(priv->regmap, item->reg +
				   MLXREG_HOTPLUG_EVENT_OFF, 0);
		if (ret)
			goto out;

		/* Set group initial status as mask and unmask group event. */
		if (item->inversed) {
			item->cache = item->mask;
			ret = regmap_write(priv->regmap, item->reg +
					   MLXREG_HOTPLUG_MASK_OFF,
					   item->mask);
			if (ret)
				goto out;
		}
	}

	/* Keep aggregation initial status as zero and unmask events. */
	ret = regmap_write(priv->regmap, pdata->cell +
			   MLXREG_HOTPLUG_AGGR_MASK_OFF, pdata->mask);
	if (ret)
		goto out;

	/* Keep low aggregation initial status as zero and unmask events. */
	if (pdata->cell_low) {
		ret = regmap_write(priv->regmap, pdata->cell_low +
				   MLXREG_HOTPLUG_AGGR_MASK_OFF,
				   pdata->mask_low);
		if (ret)
			goto out;
	}

	/* Invoke work handler for initializing hot plug devices setting. */
	mlxreg_hotplug_work_handler(&priv->dwork_irq.work);

 out:
	if (ret)
		dev_err(priv->dev, "Failed to set interrupts.\n");
	enable_irq(priv->irq);
	return ret;
}