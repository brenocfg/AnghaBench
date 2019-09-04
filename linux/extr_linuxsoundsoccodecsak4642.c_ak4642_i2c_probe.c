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
struct of_device_id {struct ak4642_drvdata* data; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct device {struct device_node* of_node; } ;
struct i2c_client {struct device dev; } ;
struct device_node {int dummy; } ;
typedef  struct regmap clk ;
struct ak4642_priv {struct regmap* mcko; struct ak4642_drvdata const* drvdata; } ;
struct ak4642_drvdata {int /*<<< orphan*/  regmap_config; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  ak4642_dai ; 
 int /*<<< orphan*/  ak4642_of_match ; 
 struct regmap* ak4642_of_parse_mcko (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct ak4642_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ak4642_priv*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  soc_component_dev_ak4642 ; 

__attribute__((used)) static int ak4642_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct device *dev = &i2c->dev;
	struct device_node *np = dev->of_node;
	const struct ak4642_drvdata *drvdata = NULL;
	struct regmap *regmap;
	struct ak4642_priv *priv;
	struct clk *mcko = NULL;

	if (np) {
		const struct of_device_id *of_id;

		mcko = ak4642_of_parse_mcko(dev);
		if (IS_ERR(mcko))
			mcko = NULL;

		of_id = of_match_device(ak4642_of_match, dev);
		if (of_id)
			drvdata = of_id->data;
	} else {
		drvdata = (const struct ak4642_drvdata *)id->driver_data;
	}

	if (!drvdata) {
		dev_err(dev, "Unknown device type\n");
		return -EINVAL;
	}

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->drvdata = drvdata;
	priv->mcko = mcko;

	i2c_set_clientdata(i2c, priv);

	regmap = devm_regmap_init_i2c(i2c, drvdata->regmap_config);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	return devm_snd_soc_register_component(dev,
				&soc_component_dev_ak4642, &ak4642_dai, 1);
}