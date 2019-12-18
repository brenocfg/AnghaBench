#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int num_inputs; struct arizona* arizona; } ;
struct wm8997_priv {TYPE_11__ core; TYPE_1__* fll; } ;
struct TYPE_18__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_4__ dev; } ;
struct arizona {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
struct TYPE_17__ {int vco_mult; } ;

/* Variables and functions */
 scalar_t__ ARIZONA_FLL1_CONTROL_1 ; 
 scalar_t__ ARIZONA_FLL2_CONTROL_1 ; 
 int /*<<< orphan*/  ARIZONA_IRQ_FLL1_CLOCK_OK ; 
 int /*<<< orphan*/  ARIZONA_IRQ_FLL1_LOCK ; 
 int /*<<< orphan*/  ARIZONA_IRQ_FLL2_CLOCK_OK ; 
 int /*<<< orphan*/  ARIZONA_IRQ_FLL2_LOCK ; 
 TYPE_1__ ARIZONA_SAMPLE_RATE_2 ; 
 int ARIZONA_SAMPLE_RATE_2_MASK ; 
 TYPE_1__ ARIZONA_SAMPLE_RATE_3 ; 
 int ARIZONA_SAMPLE_RATE_3_MASK ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CONFIG_OF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int WM8997_DIG_VU ; 
 int /*<<< orphan*/  arizona_free_spk_irqs (struct arizona*) ; 
 int /*<<< orphan*/  arizona_init_common (struct arizona*) ; 
 int /*<<< orphan*/  arizona_init_dai (TYPE_11__*,int) ; 
 int /*<<< orphan*/  arizona_init_dvfs (TYPE_11__*) ; 
 int /*<<< orphan*/  arizona_init_fll (struct arizona*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int arizona_init_spk_irqs (struct arizona*) ; 
 int arizona_init_vol_limit (struct arizona*) ; 
 int arizona_of_get_audio_pdata (struct arizona*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 struct arizona* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct wm8997_priv* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (TYPE_4__*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm8997_priv*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_4__*) ; 
 int /*<<< orphan*/  pm_runtime_idle (TYPE_4__*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,TYPE_1__,int,int) ; 
 int /*<<< orphan*/  soc_component_dev_wm8997 ; 
 TYPE_1__* wm8997_dai ; 
 TYPE_1__* wm8997_digital_vu ; 

__attribute__((used)) static int wm8997_probe(struct platform_device *pdev)
{
	struct arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	struct wm8997_priv *wm8997;
	int i, ret;

	wm8997 = devm_kzalloc(&pdev->dev, sizeof(struct wm8997_priv),
			      GFP_KERNEL);
	if (wm8997 == NULL)
		return -ENOMEM;
	platform_set_drvdata(pdev, wm8997);

	if (IS_ENABLED(CONFIG_OF)) {
		if (!dev_get_platdata(arizona->dev)) {
			ret = arizona_of_get_audio_pdata(arizona);
			if (ret < 0)
				return ret;
		}
	}

	wm8997->core.arizona = arizona;
	wm8997->core.num_inputs = 4;

	arizona_init_dvfs(&wm8997->core);

	for (i = 0; i < ARRAY_SIZE(wm8997->fll); i++)
		wm8997->fll[i].vco_mult = 1;

	arizona_init_fll(arizona, 1, ARIZONA_FLL1_CONTROL_1 - 1,
			 ARIZONA_IRQ_FLL1_LOCK, ARIZONA_IRQ_FLL1_CLOCK_OK,
			 &wm8997->fll[0]);
	arizona_init_fll(arizona, 2, ARIZONA_FLL2_CONTROL_1 - 1,
			 ARIZONA_IRQ_FLL2_LOCK, ARIZONA_IRQ_FLL2_CLOCK_OK,
			 &wm8997->fll[1]);

	/* SR2 fixed at 8kHz, SR3 fixed at 16kHz */
	regmap_update_bits(arizona->regmap, ARIZONA_SAMPLE_RATE_2,
			   ARIZONA_SAMPLE_RATE_2_MASK, 0x11);
	regmap_update_bits(arizona->regmap, ARIZONA_SAMPLE_RATE_3,
			   ARIZONA_SAMPLE_RATE_3_MASK, 0x12);

	for (i = 0; i < ARRAY_SIZE(wm8997_dai); i++)
		arizona_init_dai(&wm8997->core, i);

	/* Latch volume update bits */
	for (i = 0; i < ARRAY_SIZE(wm8997_digital_vu); i++)
		regmap_update_bits(arizona->regmap, wm8997_digital_vu[i],
				   WM8997_DIG_VU, WM8997_DIG_VU);

	pm_runtime_enable(&pdev->dev);
	pm_runtime_idle(&pdev->dev);

	arizona_init_common(arizona);

	ret = arizona_init_vol_limit(arizona);
	if (ret < 0)
		return ret;
	ret = arizona_init_spk_irqs(arizona);
	if (ret < 0)
		return ret;

	ret = devm_snd_soc_register_component(&pdev->dev,
					      &soc_component_dev_wm8997,
					      wm8997_dai,
					      ARRAY_SIZE(wm8997_dai));
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);
		goto err_spk_irqs;
	}

err_spk_irqs:
	arizona_free_spk_irqs(arizona);

	return ret;
}