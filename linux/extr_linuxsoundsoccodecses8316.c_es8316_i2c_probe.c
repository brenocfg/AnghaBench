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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct es8316_priv {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct es8316_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  es8316_dai ; 
 int /*<<< orphan*/  es8316_regmap ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct es8316_priv*) ; 
 int /*<<< orphan*/  soc_component_dev_es8316 ; 

__attribute__((used)) static int es8316_i2c_probe(struct i2c_client *i2c_client,
			    const struct i2c_device_id *id)
{
	struct es8316_priv *es8316;
	struct regmap *regmap;

	es8316 = devm_kzalloc(&i2c_client->dev, sizeof(struct es8316_priv),
			      GFP_KERNEL);
	if (es8316 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c_client, es8316);

	regmap = devm_regmap_init_i2c(i2c_client, &es8316_regmap);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	return devm_snd_soc_register_component(&i2c_client->dev,
				      &soc_component_dev_es8316,
				      &es8316_dai, 1);
}