#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ dmic2_clk_pin; scalar_t__ micbias1_vdd_3v3; scalar_t__ lout3_diff; scalar_t__ lout2_diff; scalar_t__ lout1_diff; scalar_t__ in2_diff; scalar_t__ in1_diff; } ;
struct rt5677_priv {int type; void* regmap; TYPE_1__ pdata; void* regmap_physical; void* reset_pin; void* pow_ldo2; TYPE_2__* dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_13__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
typedef  enum rt5677_type { ____Placeholder_rt5677_type } rt5677_type ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (TYPE_2__*) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 unsigned int RT5677_DEVICE_ID ; 
 scalar_t__ RT5677_DMIC_CLK2 ; 
 int /*<<< orphan*/  RT5677_GEN_CTRL2 ; 
 int /*<<< orphan*/  RT5677_GPIO5_DIR_MASK ; 
 int /*<<< orphan*/  RT5677_GPIO5_DIR_OUT ; 
 int /*<<< orphan*/  RT5677_GPIO5_FUNC_DMIC ; 
 int /*<<< orphan*/  RT5677_GPIO5_FUNC_MASK ; 
 int /*<<< orphan*/  RT5677_GPIO_CTRL2 ; 
 int /*<<< orphan*/  RT5677_IN1 ; 
 int /*<<< orphan*/  RT5677_IN_DF1 ; 
 int /*<<< orphan*/  RT5677_IN_DF2 ; 
 int /*<<< orphan*/  RT5677_LOUT1 ; 
 int /*<<< orphan*/  RT5677_LOUT1_L_DF ; 
 int /*<<< orphan*/  RT5677_LOUT2_L_DF ; 
 int /*<<< orphan*/  RT5677_LOUT3_L_DF ; 
 int /*<<< orphan*/  RT5677_MICBIAS ; 
 int /*<<< orphan*/  RT5677_MICBIAS1_CTRL_VDD_3_3V ; 
 int /*<<< orphan*/  RT5677_MICBIAS1_CTRL_VDD_MASK ; 
 int /*<<< orphan*/  RT5677_RESET ; 
 int /*<<< orphan*/  RT5677_VENDOR_ID2 ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*,int) ; 
 void* devm_gpiod_get_optional (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 struct rt5677_priv* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 void* devm_regmap_init (TYPE_2__*,int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 
 void* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rt5677_priv*) ; 
 int /*<<< orphan*/  init_list ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  regmap_read (void*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_register_patch (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt5677_acpi_match ; 
 int /*<<< orphan*/  rt5677_dai ; 
 int /*<<< orphan*/  rt5677_init_gpio (struct i2c_client*) ; 
 int rt5677_init_irq (struct i2c_client*) ; 
 int /*<<< orphan*/  rt5677_of_match ; 
 int /*<<< orphan*/  rt5677_read_device_properties (struct rt5677_priv*,TYPE_2__*) ; 
 int /*<<< orphan*/  rt5677_regmap ; 
 int /*<<< orphan*/  rt5677_regmap_physical ; 
 int /*<<< orphan*/  soc_component_dev_rt5677 ; 

__attribute__((used)) static int rt5677_i2c_probe(struct i2c_client *i2c)
{
	struct rt5677_priv *rt5677;
	int ret;
	unsigned int val;

	rt5677 = devm_kzalloc(&i2c->dev, sizeof(struct rt5677_priv),
				GFP_KERNEL);
	if (rt5677 == NULL)
		return -ENOMEM;

	rt5677->dev = &i2c->dev;
	i2c_set_clientdata(i2c, rt5677);

	if (i2c->dev.of_node) {
		const struct of_device_id *match_id;

		match_id = of_match_device(rt5677_of_match, &i2c->dev);
		if (match_id)
			rt5677->type = (enum rt5677_type)match_id->data;
	} else if (ACPI_HANDLE(&i2c->dev)) {
		const struct acpi_device_id *acpi_id;

		acpi_id = acpi_match_device(rt5677_acpi_match, &i2c->dev);
		if (acpi_id)
			rt5677->type = (enum rt5677_type)acpi_id->driver_data;
	} else {
		return -EINVAL;
	}

	rt5677_read_device_properties(rt5677, &i2c->dev);

	/* pow-ldo2 and reset are optional. The codec pins may be statically
	 * connected on the board without gpios. If the gpio device property
	 * isn't specified, devm_gpiod_get_optional returns NULL.
	 */
	rt5677->pow_ldo2 = devm_gpiod_get_optional(&i2c->dev,
			"realtek,pow-ldo2", GPIOD_OUT_HIGH);
	if (IS_ERR(rt5677->pow_ldo2)) {
		ret = PTR_ERR(rt5677->pow_ldo2);
		dev_err(&i2c->dev, "Failed to request POW_LDO2: %d\n", ret);
		return ret;
	}
	rt5677->reset_pin = devm_gpiod_get_optional(&i2c->dev,
			"realtek,reset", GPIOD_OUT_LOW);
	if (IS_ERR(rt5677->reset_pin)) {
		ret = PTR_ERR(rt5677->reset_pin);
		dev_err(&i2c->dev, "Failed to request RESET: %d\n", ret);
		return ret;
	}

	if (rt5677->pow_ldo2 || rt5677->reset_pin) {
		/* Wait a while until I2C bus becomes available. The datasheet
		 * does not specify the exact we should wait but startup
		 * sequence mentiones at least a few milliseconds.
		 */
		msleep(10);
	}

	rt5677->regmap_physical = devm_regmap_init_i2c(i2c,
					&rt5677_regmap_physical);
	if (IS_ERR(rt5677->regmap_physical)) {
		ret = PTR_ERR(rt5677->regmap_physical);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	rt5677->regmap = devm_regmap_init(&i2c->dev, NULL, i2c, &rt5677_regmap);
	if (IS_ERR(rt5677->regmap)) {
		ret = PTR_ERR(rt5677->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	regmap_read(rt5677->regmap, RT5677_VENDOR_ID2, &val);
	if (val != RT5677_DEVICE_ID) {
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt5677\n", val);
		return -ENODEV;
	}

	regmap_write(rt5677->regmap, RT5677_RESET, 0x10ec);

	ret = regmap_register_patch(rt5677->regmap, init_list,
				    ARRAY_SIZE(init_list));
	if (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	if (rt5677->pdata.in1_diff)
		regmap_update_bits(rt5677->regmap, RT5677_IN1,
					RT5677_IN_DF1, RT5677_IN_DF1);

	if (rt5677->pdata.in2_diff)
		regmap_update_bits(rt5677->regmap, RT5677_IN1,
					RT5677_IN_DF2, RT5677_IN_DF2);

	if (rt5677->pdata.lout1_diff)
		regmap_update_bits(rt5677->regmap, RT5677_LOUT1,
					RT5677_LOUT1_L_DF, RT5677_LOUT1_L_DF);

	if (rt5677->pdata.lout2_diff)
		regmap_update_bits(rt5677->regmap, RT5677_LOUT1,
					RT5677_LOUT2_L_DF, RT5677_LOUT2_L_DF);

	if (rt5677->pdata.lout3_diff)
		regmap_update_bits(rt5677->regmap, RT5677_LOUT1,
					RT5677_LOUT3_L_DF, RT5677_LOUT3_L_DF);

	if (rt5677->pdata.dmic2_clk_pin == RT5677_DMIC_CLK2) {
		regmap_update_bits(rt5677->regmap, RT5677_GEN_CTRL2,
					RT5677_GPIO5_FUNC_MASK,
					RT5677_GPIO5_FUNC_DMIC);
		regmap_update_bits(rt5677->regmap, RT5677_GPIO_CTRL2,
					RT5677_GPIO5_DIR_MASK,
					RT5677_GPIO5_DIR_OUT);
	}

	if (rt5677->pdata.micbias1_vdd_3v3)
		regmap_update_bits(rt5677->regmap, RT5677_MICBIAS,
			RT5677_MICBIAS1_CTRL_VDD_MASK,
			RT5677_MICBIAS1_CTRL_VDD_3_3V);

	rt5677_init_gpio(i2c);
	ret = rt5677_init_irq(i2c);
	if (ret)
		dev_err(&i2c->dev, "Failed to initialize irq: %d\n", ret);

	return devm_snd_soc_register_component(&i2c->dev,
				      &soc_component_dev_rt5677,
				      rt5677_dai, ARRAY_SIZE(rt5677_dai));
}