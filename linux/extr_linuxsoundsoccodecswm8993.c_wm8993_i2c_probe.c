#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wm8993_priv {TYPE_1__* supplies; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * dev; int /*<<< orphan*/  fll_lock; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM8993_GPIO1 ; 
 int WM8993_GPIO1_PD ; 
 int WM8993_GPIO1_SEL_MASK ; 
 int /*<<< orphan*/  WM8993_SOFTWARE_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct wm8993_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct wm8993_priv*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wm8993_priv*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct wm8993_priv*) ; 
 int /*<<< orphan*/  soc_component_dev_wm8993 ; 
 int /*<<< orphan*/  wm8993_dai ; 
 int /*<<< orphan*/  wm8993_irq ; 
 int /*<<< orphan*/  wm8993_regmap ; 
 TYPE_1__* wm8993_regmap_patch ; 
 int /*<<< orphan*/ * wm8993_supply_names ; 

__attribute__((used)) static int wm8993_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8993_priv *wm8993;
	unsigned int reg;
	int ret, i;

	wm8993 = devm_kzalloc(&i2c->dev, sizeof(struct wm8993_priv),
			      GFP_KERNEL);
	if (wm8993 == NULL)
		return -ENOMEM;

	wm8993->dev = &i2c->dev;
	init_completion(&wm8993->fll_lock);

	wm8993->regmap = devm_regmap_init_i2c(i2c, &wm8993_regmap);
	if (IS_ERR(wm8993->regmap)) {
		ret = PTR_ERR(wm8993->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(i2c, wm8993);

	for (i = 0; i < ARRAY_SIZE(wm8993->supplies); i++)
		wm8993->supplies[i].supply = wm8993_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(wm8993->supplies),
				 wm8993->supplies);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8993->supplies),
				    wm8993->supplies);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	ret = regmap_read(wm8993->regmap, WM8993_SOFTWARE_RESET, &reg);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to read chip ID: %d\n", ret);
		goto err_enable;
	}

	if (reg != 0x8993) {
		dev_err(&i2c->dev, "Invalid ID register value %x\n", reg);
		ret = -EINVAL;
		goto err_enable;
	}

	ret = regmap_write(wm8993->regmap, WM8993_SOFTWARE_RESET, 0xffff);
	if (ret != 0)
		goto err_enable;

	ret = regmap_register_patch(wm8993->regmap, wm8993_regmap_patch,
				    ARRAY_SIZE(wm8993_regmap_patch));
	if (ret != 0)
		dev_warn(wm8993->dev, "Failed to apply regmap patch: %d\n",
			 ret);

	if (i2c->irq) {
		/* Put GPIO1 into interrupt mode (only GPIO1 can output IRQ) */
		ret = regmap_update_bits(wm8993->regmap, WM8993_GPIO1,
					 WM8993_GPIO1_PD |
					 WM8993_GPIO1_SEL_MASK, 7);
		if (ret != 0)
			goto err_enable;

		ret = request_threaded_irq(i2c->irq, NULL, wm8993_irq,
					   IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					   "wm8993", wm8993);
		if (ret != 0)
			goto err_enable;

	}

	regulator_bulk_disable(ARRAY_SIZE(wm8993->supplies), wm8993->supplies);

	regcache_cache_only(wm8993->regmap, true);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_wm8993, &wm8993_dai, 1);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);
		goto err_irq;
	}

	return 0;

err_irq:
	if (i2c->irq)
		free_irq(i2c->irq, wm8993);
err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8993->supplies), wm8993->supplies);
	return ret;
}