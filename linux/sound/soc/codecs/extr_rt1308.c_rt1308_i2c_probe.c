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
struct rt1308_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 unsigned int RT1308_DEVICE_ID_NUM ; 
 int /*<<< orphan*/  RT1308_VEN_DEV_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 struct rt1308_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rt1308_priv*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  rt1308_dai ; 
 int /*<<< orphan*/  rt1308_efuse (struct rt1308_priv*) ; 
 int /*<<< orphan*/  rt1308_regmap ; 
 int /*<<< orphan*/  soc_component_dev_rt1308 ; 

__attribute__((used)) static int rt1308_i2c_probe(struct i2c_client *i2c,
		    const struct i2c_device_id *id)
{
	struct rt1308_priv *rt1308;
	int ret;
	unsigned int val;

	rt1308 = devm_kzalloc(&i2c->dev, sizeof(struct rt1308_priv),
				GFP_KERNEL);
	if (rt1308 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, rt1308);

	rt1308->regmap = devm_regmap_init_i2c(i2c, &rt1308_regmap);
	if (IS_ERR(rt1308->regmap)) {
		ret = PTR_ERR(rt1308->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	regmap_read(rt1308->regmap, RT1308_VEN_DEV_ID, &val);
	/* ignore last byte difference */
	if ((val & 0xFFFFFF00) != RT1308_DEVICE_ID_NUM) {
		dev_err(&i2c->dev,
			"Device with ID register %x is not rt1308\n", val);
		return -ENODEV;
	}

	rt1308_efuse(rt1308);

	return devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_rt1308,
			rt1308_dai, ARRAY_SIZE(rt1308_dai));
}