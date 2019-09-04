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
struct cs4271_private {struct regmap* regmap; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int cs4271_common_probe (struct device*,struct cs4271_private**) ; 
 int /*<<< orphan*/  cs4271_dai ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct cs4271_private*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  soc_component_dev_cs4271 ; 

int cs4271_probe(struct device *dev, struct regmap *regmap)
{
	struct cs4271_private *cs4271;
	int ret;

	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	ret = cs4271_common_probe(dev, &cs4271);
	if (ret < 0)
		return ret;

	dev_set_drvdata(dev, cs4271);
	cs4271->regmap = regmap;

	return devm_snd_soc_register_component(dev, &soc_component_dev_cs4271,
					       &cs4271_dai, 1);
}