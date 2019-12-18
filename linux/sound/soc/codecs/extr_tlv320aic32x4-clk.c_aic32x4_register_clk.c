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
struct device {int dummy; } ;
struct clk_init_data {scalar_t__ flags; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; int /*<<< orphan*/  name; int /*<<< orphan*/  ops; } ;
struct TYPE_3__ {struct clk_init_data* init; } ;
struct clk_aic32x4 {TYPE_1__ hw; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; struct device* dev; } ;
struct clk {int dummy; } ;
struct aic32x4_clkdesc {int /*<<< orphan*/  name; int /*<<< orphan*/  reg; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clk_hw_register_clkdev (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dev_get_regmap (struct device*,int /*<<< orphan*/ *) ; 
 char* dev_name (struct device*) ; 
 struct clk* devm_clk_register (struct device*,TYPE_1__*) ; 
 struct clk_aic32x4* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk *aic32x4_register_clk(struct device *dev,
			struct aic32x4_clkdesc *desc)
{
	struct clk_init_data init;
	struct clk_aic32x4 *priv;
	const char *devname = dev_name(dev);

	init.ops = desc->ops;
	init.name = desc->name;
	init.parent_names = desc->parent_names;
	init.num_parents = desc->num_parents;
	init.flags = 0;

	priv = devm_kzalloc(dev, sizeof(struct clk_aic32x4), GFP_KERNEL);
	if (priv == NULL)
		return (struct clk *) -ENOMEM;

	priv->dev = dev;
	priv->hw.init = &init;
	priv->regmap = dev_get_regmap(dev, NULL);
	priv->reg = desc->reg;

	clk_hw_register_clkdev(&priv->hw, desc->name, devname);
	return devm_clk_register(dev, &priv->hw);
}