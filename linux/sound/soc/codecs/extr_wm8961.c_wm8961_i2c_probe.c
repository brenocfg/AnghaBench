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
struct wm8961_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 unsigned int WM8961_CHIP_REV_MASK ; 
 unsigned int WM8961_CHIP_REV_SHIFT ; 
 unsigned int WM8961_DEVICE_ID_MASK ; 
 unsigned int WM8961_DEVICE_ID_SHIFT ; 
 int /*<<< orphan*/  WM8961_RIGHT_INPUT_VOLUME ; 
 int /*<<< orphan*/  WM8961_SOFTWARE_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 struct wm8961_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wm8961_priv*) ; 
 int /*<<< orphan*/  regcache_cache_bypass (int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  soc_component_dev_wm8961 ; 
 int /*<<< orphan*/  wm8961_dai ; 
 int /*<<< orphan*/  wm8961_regmap ; 

__attribute__((used)) static int wm8961_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8961_priv *wm8961;
	unsigned int val;
	int ret;

	wm8961 = devm_kzalloc(&i2c->dev, sizeof(struct wm8961_priv),
			      GFP_KERNEL);
	if (wm8961 == NULL)
		return -ENOMEM;

	wm8961->regmap = devm_regmap_init_i2c(i2c, &wm8961_regmap);
	if (IS_ERR(wm8961->regmap))
		return PTR_ERR(wm8961->regmap);

	ret = regmap_read(wm8961->regmap, WM8961_SOFTWARE_RESET, &val);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to read chip ID: %d\n", ret);
		return ret;
	}

	if (val != 0x1801) {
		dev_err(&i2c->dev, "Device is not a WM8961: ID=0x%x\n", val);
		return -EINVAL;
	}

	/* This isn't volatile - readback doesn't correspond to write */
	regcache_cache_bypass(wm8961->regmap, true);
	ret = regmap_read(wm8961->regmap, WM8961_RIGHT_INPUT_VOLUME, &val);
	regcache_cache_bypass(wm8961->regmap, false);

	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to read chip revision: %d\n", ret);
		return ret;
	}

	dev_info(&i2c->dev, "WM8961 family %d revision %c\n",
		 (val & WM8961_DEVICE_ID_MASK) >> WM8961_DEVICE_ID_SHIFT,
		 ((val & WM8961_CHIP_REV_MASK) >> WM8961_CHIP_REV_SHIFT)
		 + 'A');

	ret = regmap_write(wm8961->regmap, WM8961_SOFTWARE_RESET, 0x1801);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to issue reset: %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(i2c, wm8961);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_wm8961, &wm8961_dai, 1);

	return ret;
}