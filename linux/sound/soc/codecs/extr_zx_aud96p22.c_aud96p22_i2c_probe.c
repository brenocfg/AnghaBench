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
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct aud96p22_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aud96p22_dai ; 
 int /*<<< orphan*/  aud96p22_driver ; 
 int /*<<< orphan*/  aud96p22_regmap ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct aud96p22_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct aud96p22_priv*) ; 

__attribute__((used)) static int aud96p22_i2c_probe(struct i2c_client *i2c,
			      const struct i2c_device_id *id)
{
	struct device *dev = &i2c->dev;
	struct aud96p22_priv *priv;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;

	priv->regmap = devm_regmap_init_i2c(i2c, &aud96p22_regmap);
	if (IS_ERR(priv->regmap)) {
		ret = PTR_ERR(priv->regmap);
		dev_err(dev, "failed to init i2c regmap: %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(i2c, priv);

	ret = devm_snd_soc_register_component(dev, &aud96p22_driver, &aud96p22_dai, 1);
	if (ret) {
		dev_err(dev, "failed to register component: %d\n", ret);
		return ret;
	}

	return 0;
}