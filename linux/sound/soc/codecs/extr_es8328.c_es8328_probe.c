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
struct regmap {int dummy; } ;
struct es8328_priv {TYPE_1__* supplies; struct regmap* regmap; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct es8328_priv*) ; 
 struct es8328_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  es8328_component_driver ; 
 int /*<<< orphan*/  es8328_dai ; 
 int /*<<< orphan*/ * supply_names ; 

int es8328_probe(struct device *dev, struct regmap *regmap)
{
	struct es8328_priv *es8328;
	int ret;
	int i;

	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	es8328 = devm_kzalloc(dev, sizeof(*es8328), GFP_KERNEL);
	if (es8328 == NULL)
		return -ENOMEM;

	es8328->regmap = regmap;

	for (i = 0; i < ARRAY_SIZE(es8328->supplies); i++)
		es8328->supplies[i].supply = supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(es8328->supplies),
				es8328->supplies);
	if (ret) {
		dev_err(dev, "unable to get regulators\n");
		return ret;
	}

	dev_set_drvdata(dev, es8328);

	return devm_snd_soc_register_component(dev,
			&es8328_component_driver, &es8328_dai, 1);
}