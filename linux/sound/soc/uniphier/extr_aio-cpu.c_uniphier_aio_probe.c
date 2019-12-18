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
struct uniphier_aio_sub {int /*<<< orphan*/  lock; struct uniphier_aio* aio; } ;
struct uniphier_aio_pll {int dummy; } ;
struct uniphier_aio_chip {int num_aios; int num_wup_aios; int num_plls; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * rst; TYPE_1__* chip_spec; struct platform_device* pdev; struct uniphier_aio* aios; void* plls; int /*<<< orphan*/ * regmap_sg; } ;
struct uniphier_aio {struct uniphier_aio_sub* sub; int /*<<< orphan*/  fmt; struct uniphier_aio_chip* chip; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int num_dais; int num_plls; int /*<<< orphan*/  dais; int /*<<< orphan*/  plls; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct uniphier_aio_sub*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SND_SOC_DAIFMT_I2S ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,char*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct uniphier_aio_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_reset_control_get_shared (struct device*,char*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uniphier_aio_chip*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ *) ; 
 int reset_control_deassert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uniphier_aio_component ; 
 int uniphier_aiodma_soc_register_platform (struct platform_device*) ; 

int uniphier_aio_probe(struct platform_device *pdev)
{
	struct uniphier_aio_chip *chip;
	struct device *dev = &pdev->dev;
	int ret, i, j;

	chip = devm_kzalloc(dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->chip_spec = of_device_get_match_data(dev);
	if (!chip->chip_spec)
		return -EINVAL;

	chip->regmap_sg = syscon_regmap_lookup_by_phandle(dev->of_node,
							  "socionext,syscon");
	if (IS_ERR(chip->regmap_sg)) {
		if (PTR_ERR(chip->regmap_sg) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		chip->regmap_sg = NULL;
	}

	chip->clk = devm_clk_get(dev, "aio");
	if (IS_ERR(chip->clk))
		return PTR_ERR(chip->clk);

	chip->rst = devm_reset_control_get_shared(dev, "aio");
	if (IS_ERR(chip->rst))
		return PTR_ERR(chip->rst);

	chip->num_aios = chip->chip_spec->num_dais;
	chip->num_wup_aios = chip->num_aios;
	chip->aios = devm_kcalloc(dev,
				  chip->num_aios, sizeof(struct uniphier_aio),
				  GFP_KERNEL);
	if (!chip->aios)
		return -ENOMEM;

	chip->num_plls = chip->chip_spec->num_plls;
	chip->plls = devm_kcalloc(dev,
				  chip->num_plls,
				  sizeof(struct uniphier_aio_pll),
				  GFP_KERNEL);
	if (!chip->plls)
		return -ENOMEM;
	memcpy(chip->plls, chip->chip_spec->plls,
	       sizeof(struct uniphier_aio_pll) * chip->num_plls);

	for (i = 0; i < chip->num_aios; i++) {
		struct uniphier_aio *aio = &chip->aios[i];

		aio->chip = chip;
		aio->fmt = SND_SOC_DAIFMT_I2S;

		for (j = 0; j < ARRAY_SIZE(aio->sub); j++) {
			struct uniphier_aio_sub *sub = &aio->sub[j];

			sub->aio = aio;
			spin_lock_init(&sub->lock);
		}
	}

	chip->pdev = pdev;
	platform_set_drvdata(pdev, chip);

	ret = clk_prepare_enable(chip->clk);
	if (ret)
		return ret;

	ret = reset_control_deassert(chip->rst);
	if (ret)
		goto err_out_clock;

	ret = devm_snd_soc_register_component(dev, &uniphier_aio_component,
					      chip->chip_spec->dais,
					      chip->chip_spec->num_dais);
	if (ret) {
		dev_err(dev, "Register component failed.\n");
		goto err_out_reset;
	}

	ret = uniphier_aiodma_soc_register_platform(pdev);
	if (ret) {
		dev_err(dev, "Register platform failed.\n");
		goto err_out_reset;
	}

	return 0;

err_out_reset:
	reset_control_assert(chip->rst);

err_out_clock:
	clk_disable_unprepare(chip->clk);

	return ret;
}