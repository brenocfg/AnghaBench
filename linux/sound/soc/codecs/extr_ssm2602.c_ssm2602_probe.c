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
struct ssm2602_priv {int type; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
typedef  enum ssm2602_type { ____Placeholder_ssm2602_type } ssm2602_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct ssm2602_priv*) ; 
 struct ssm2602_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  soc_component_dev_ssm2602 ; 
 int /*<<< orphan*/  ssm2602_dai ; 

int ssm2602_probe(struct device *dev, enum ssm2602_type type,
	struct regmap *regmap)
{
	struct ssm2602_priv *ssm2602;

	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	ssm2602 = devm_kzalloc(dev, sizeof(*ssm2602), GFP_KERNEL);
	if (ssm2602 == NULL)
		return -ENOMEM;

	dev_set_drvdata(dev, ssm2602);
	ssm2602->type = type;
	ssm2602->regmap = regmap;

	return devm_snd_soc_register_component(dev, &soc_component_dev_ssm2602,
		&ssm2602_dai, 1);
}