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
struct aic23 {struct regmap* regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct aic23*) ; 
 struct aic23* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  soc_component_dev_tlv320aic23 ; 
 int /*<<< orphan*/  tlv320aic23_dai ; 

int tlv320aic23_probe(struct device *dev, struct regmap *regmap)
{
	struct aic23 *aic23;

	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	aic23 = devm_kzalloc(dev, sizeof(struct aic23), GFP_KERNEL);
	if (aic23 == NULL)
		return -ENOMEM;

	aic23->regmap = regmap;

	dev_set_drvdata(dev, aic23);

	return devm_snd_soc_register_component(dev,
				      &soc_component_dev_tlv320aic23,
				      &tlv320aic23_dai, 1);
}