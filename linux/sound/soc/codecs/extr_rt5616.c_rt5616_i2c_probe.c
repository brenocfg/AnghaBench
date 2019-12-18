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
struct rt5616_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT5616_DEVICE_ID ; 
 int /*<<< orphan*/  RT5616_PWR_ANLG1 ; 
 int RT5616_PWR_BG ; 
 int RT5616_PWR_FV1 ; 
 int RT5616_PWR_FV2 ; 
 int RT5616_PWR_LDO_DVO_1_2V ; 
 int RT5616_PWR_LDO_DVO_MASK ; 
 int RT5616_PWR_MB ; 
 int RT5616_PWR_VREF1 ; 
 int RT5616_PWR_VREF2 ; 
 int /*<<< orphan*/  RT5616_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct rt5616_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rt5616_priv*) ; 
 int /*<<< orphan*/  init_list ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5616_dai ; 
 int /*<<< orphan*/  rt5616_regmap ; 
 int /*<<< orphan*/  soc_component_dev_rt5616 ; 

__attribute__((used)) static int rt5616_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct rt5616_priv *rt5616;
	unsigned int val;
	int ret;

	rt5616 = devm_kzalloc(&i2c->dev, sizeof(struct rt5616_priv),
			      GFP_KERNEL);
	if (!rt5616)
		return -ENOMEM;

	i2c_set_clientdata(i2c, rt5616);

	rt5616->regmap = devm_regmap_init_i2c(i2c, &rt5616_regmap);
	if (IS_ERR(rt5616->regmap)) {
		ret = PTR_ERR(rt5616->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	regmap_read(rt5616->regmap, RT5616_DEVICE_ID, &val);
	if (val != 0x6281) {
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5616\n",
			val);
		return -ENODEV;
	}
	regmap_write(rt5616->regmap, RT5616_RESET, 0);
	regmap_update_bits(rt5616->regmap, RT5616_PWR_ANLG1,
			   RT5616_PWR_VREF1 | RT5616_PWR_MB |
			   RT5616_PWR_BG | RT5616_PWR_VREF2,
			   RT5616_PWR_VREF1 | RT5616_PWR_MB |
			   RT5616_PWR_BG | RT5616_PWR_VREF2);
	mdelay(10);
	regmap_update_bits(rt5616->regmap, RT5616_PWR_ANLG1,
			   RT5616_PWR_FV1 | RT5616_PWR_FV2,
			   RT5616_PWR_FV1 | RT5616_PWR_FV2);

	ret = regmap_register_patch(rt5616->regmap, init_list,
				    ARRAY_SIZE(init_list));
	if (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	regmap_update_bits(rt5616->regmap, RT5616_PWR_ANLG1,
			   RT5616_PWR_LDO_DVO_MASK, RT5616_PWR_LDO_DVO_1_2V);

	return devm_snd_soc_register_component(&i2c->dev,
				      &soc_component_dev_rt5616,
				      rt5616_dai, ARRAY_SIZE(rt5616_dai));
}