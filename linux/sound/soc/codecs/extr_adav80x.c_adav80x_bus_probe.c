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
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct adav80x {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  adav80x_component_driver ; 
 int /*<<< orphan*/  adav80x_dais ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct adav80x*) ; 
 struct adav80x* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int adav80x_bus_probe(struct device *dev, struct regmap *regmap)
{
	struct adav80x *adav80x;

	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	adav80x = devm_kzalloc(dev, sizeof(*adav80x), GFP_KERNEL);
	if (!adav80x)
		return -ENOMEM;

	dev_set_drvdata(dev, adav80x);
	adav80x->regmap = regmap;

	return devm_snd_soc_register_component(dev, &adav80x_component_driver,
		adav80x_dais, ARRAY_SIZE(adav80x_dais));
}