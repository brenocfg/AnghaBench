#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wm8804_priv {TYPE_1__* supplies; int /*<<< orphan*/  reset; TYPE_3__* disable_nb; struct regmap* regmap; struct device* dev; } ;
struct regulator {int dummy; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_6__ {struct regulator* consumer; int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM8804_DEVID2 ; 
 int /*<<< orphan*/  WM8804_DEVREV ; 
 int /*<<< orphan*/  WM8804_RST_DEVID1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct wm8804_priv*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct wm8804_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int devm_regulator_register_notifier (struct regulator*,TYPE_3__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_idle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  soc_component_dev_wm8804 ; 
 int /*<<< orphan*/  wm8804_dai ; 
 int /*<<< orphan*/  wm8804_regulator_event_0 ; 
 int /*<<< orphan*/  wm8804_regulator_event_1 ; 
 int wm8804_soft_reset (struct wm8804_priv*) ; 
 int /*<<< orphan*/ * wm8804_supply_names ; 

int wm8804_probe(struct device *dev, struct regmap *regmap)
{
	struct wm8804_priv *wm8804;
	unsigned int id1, id2;
	int i, ret;

	wm8804 = devm_kzalloc(dev, sizeof(*wm8804), GFP_KERNEL);
	if (!wm8804)
		return -ENOMEM;

	dev_set_drvdata(dev, wm8804);

	wm8804->dev = dev;
	wm8804->regmap = regmap;

	wm8804->reset = devm_gpiod_get_optional(dev, "wlf,reset",
						GPIOD_OUT_LOW);
	if (IS_ERR(wm8804->reset)) {
		ret = PTR_ERR(wm8804->reset);
		dev_err(dev, "Failed to get reset line: %d\n", ret);
		return ret;
	}

	for (i = 0; i < ARRAY_SIZE(wm8804->supplies); i++)
		wm8804->supplies[i].supply = wm8804_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(wm8804->supplies),
				      wm8804->supplies);
	if (ret) {
		dev_err(dev, "Failed to request supplies: %d\n", ret);
		return ret;
	}

	wm8804->disable_nb[0].notifier_call = wm8804_regulator_event_0;
	wm8804->disable_nb[1].notifier_call = wm8804_regulator_event_1;

	/* This should really be moved into the regulator core */
	for (i = 0; i < ARRAY_SIZE(wm8804->supplies); i++) {
		struct regulator *regulator = wm8804->supplies[i].consumer;

		ret = devm_regulator_register_notifier(regulator,
						       &wm8804->disable_nb[i]);
		if (ret != 0) {
			dev_err(dev,
				"Failed to register regulator notifier: %d\n",
				ret);
			return ret;
		}
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8804->supplies),
				    wm8804->supplies);
	if (ret) {
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	gpiod_set_value_cansleep(wm8804->reset, 1);

	ret = regmap_read(regmap, WM8804_RST_DEVID1, &id1);
	if (ret < 0) {
		dev_err(dev, "Failed to read device ID: %d\n", ret);
		goto err_reg_enable;
	}

	ret = regmap_read(regmap, WM8804_DEVID2, &id2);
	if (ret < 0) {
		dev_err(dev, "Failed to read device ID: %d\n", ret);
		goto err_reg_enable;
	}

	id2 = (id2 << 8) | id1;

	if (id2 != 0x8805) {
		dev_err(dev, "Invalid device ID: %#x\n", id2);
		ret = -EINVAL;
		goto err_reg_enable;
	}

	ret = regmap_read(regmap, WM8804_DEVREV, &id1);
	if (ret < 0) {
		dev_err(dev, "Failed to read device revision: %d\n",
			ret);
		goto err_reg_enable;
	}
	dev_info(dev, "revision %c\n", id1 + 'A');

	if (!wm8804->reset) {
		ret = wm8804_soft_reset(wm8804);
		if (ret < 0) {
			dev_err(dev, "Failed to issue reset: %d\n", ret);
			goto err_reg_enable;
		}
	}

	ret = devm_snd_soc_register_component(dev, &soc_component_dev_wm8804,
				     &wm8804_dai, 1);
	if (ret < 0) {
		dev_err(dev, "Failed to register CODEC: %d\n", ret);
		goto err_reg_enable;
	}

	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	pm_runtime_idle(dev);

	return 0;

err_reg_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8804->supplies), wm8804->supplies);
	return ret;
}