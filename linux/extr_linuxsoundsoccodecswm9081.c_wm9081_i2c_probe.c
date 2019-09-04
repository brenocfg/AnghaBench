#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  irq_cmos; scalar_t__ irq_high; } ;
struct wm9081_priv {int /*<<< orphan*/  regmap; TYPE_1__ pdata; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM9081_INTERRUPT_CONTROL ; 
 unsigned int WM9081_IRQ_OP_CTRL ; 
 unsigned int WM9081_IRQ_POL ; 
 int /*<<< orphan*/  WM9081_SOFTWARE_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct wm9081_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wm9081_priv*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  soc_component_dev_wm9081 ; 
 int /*<<< orphan*/  wm9081_dai ; 
 int /*<<< orphan*/  wm9081_regmap ; 
 int wm9081_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm9081_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm9081_priv *wm9081;
	unsigned int reg;
	int ret;

	wm9081 = devm_kzalloc(&i2c->dev, sizeof(struct wm9081_priv),
			      GFP_KERNEL);
	if (wm9081 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, wm9081);

	wm9081->regmap = devm_regmap_init_i2c(i2c, &wm9081_regmap);
	if (IS_ERR(wm9081->regmap)) {
		ret = PTR_ERR(wm9081->regmap);
		dev_err(&i2c->dev, "regmap_init() failed: %d\n", ret);
		return ret;
	}

	ret = regmap_read(wm9081->regmap, WM9081_SOFTWARE_RESET, &reg);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to read chip ID: %d\n", ret);
		return ret;
	}
	if (reg != 0x9081) {
		dev_err(&i2c->dev, "Device is not a WM9081: ID=0x%x\n", reg);
		return -EINVAL;
	}

	ret = wm9081_reset(wm9081->regmap);
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to issue reset\n");
		return ret;
	}

	if (dev_get_platdata(&i2c->dev))
		memcpy(&wm9081->pdata, dev_get_platdata(&i2c->dev),
		       sizeof(wm9081->pdata));

	reg = 0;
	if (wm9081->pdata.irq_high)
		reg |= WM9081_IRQ_POL;
	if (!wm9081->pdata.irq_cmos)
		reg |= WM9081_IRQ_OP_CTRL;
	regmap_update_bits(wm9081->regmap, WM9081_INTERRUPT_CONTROL,
			   WM9081_IRQ_POL | WM9081_IRQ_OP_CTRL, reg);

	regcache_cache_only(wm9081->regmap, true);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_wm9081, &wm9081_dai, 1);
	if (ret < 0)
		return ret;

	return 0;
}