#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wm8770_priv {int /*<<< orphan*/  regmap; TYPE_1__* disable_nb; TYPE_2__* supplies; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  consumer; int /*<<< orphan*/  supply; } ;
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct wm8770_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int devm_regulator_register_notifier (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  soc_component_dev_wm8770 ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct wm8770_priv*) ; 
 int /*<<< orphan*/  wm8770_dai ; 
 int /*<<< orphan*/  wm8770_regmap ; 
 int /*<<< orphan*/  wm8770_regulator_event_0 ; 
 int /*<<< orphan*/  wm8770_regulator_event_1 ; 
 int /*<<< orphan*/  wm8770_regulator_event_2 ; 
 int /*<<< orphan*/ * wm8770_supply_names ; 

__attribute__((used)) static int wm8770_spi_probe(struct spi_device *spi)
{
	struct wm8770_priv *wm8770;
	int ret, i;

	wm8770 = devm_kzalloc(&spi->dev, sizeof(struct wm8770_priv),
			      GFP_KERNEL);
	if (!wm8770)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(wm8770->supplies); i++)
		wm8770->supplies[i].supply = wm8770_supply_names[i];

	ret = devm_regulator_bulk_get(&spi->dev, ARRAY_SIZE(wm8770->supplies),
				      wm8770->supplies);
	if (ret) {
		dev_err(&spi->dev, "Failed to request supplies: %d\n", ret);
		return ret;
	}

	wm8770->disable_nb[0].notifier_call = wm8770_regulator_event_0;
	wm8770->disable_nb[1].notifier_call = wm8770_regulator_event_1;
	wm8770->disable_nb[2].notifier_call = wm8770_regulator_event_2;

	/* This should really be moved into the regulator core */
	for (i = 0; i < ARRAY_SIZE(wm8770->supplies); i++) {
		ret = devm_regulator_register_notifier(
						wm8770->supplies[i].consumer,
						&wm8770->disable_nb[i]);
		if (ret) {
			dev_err(&spi->dev,
				"Failed to register regulator notifier: %d\n",
				ret);
		}
	}

	wm8770->regmap = devm_regmap_init_spi(spi, &wm8770_regmap);
	if (IS_ERR(wm8770->regmap))
		return PTR_ERR(wm8770->regmap);

	spi_set_drvdata(spi, wm8770);

	ret = devm_snd_soc_register_component(&spi->dev,
				     &soc_component_dev_wm8770, &wm8770_dai, 1);

	return ret;
}