#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;

/* Type definitions */
struct TYPE_19__ {int num_inputs; TYPE_1__* adsp; struct arizona* arizona; } ;
struct wm5102_priv {TYPE_14__ core; TYPE_2__* fll; } ;
struct TYPE_22__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_6__ dev; } ;
struct arizona {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  dac_comp_lock; } ;
struct TYPE_21__ {int vco_mult; } ;
struct TYPE_20__ {char* part; int num; int num_mems; TYPE_2__* mem; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  base; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_DSP1_CONTROL_1 ; 
 scalar_t__ ARIZONA_FLL1_CONTROL_1 ; 
 scalar_t__ ARIZONA_FLL2_CONTROL_1 ; 
 int /*<<< orphan*/  ARIZONA_IRQ_DSP_IRQ1 ; 
 int /*<<< orphan*/  ARIZONA_IRQ_FLL1_CLOCK_OK ; 
 int /*<<< orphan*/  ARIZONA_IRQ_FLL1_LOCK ; 
 int /*<<< orphan*/  ARIZONA_IRQ_FLL2_CLOCK_OK ; 
 int /*<<< orphan*/  ARIZONA_IRQ_FLL2_LOCK ; 
 TYPE_2__ ARIZONA_SAMPLE_RATE_2 ; 
 int ARIZONA_SAMPLE_RATE_2_MASK ; 
 TYPE_2__ ARIZONA_SAMPLE_RATE_3 ; 
 int ARIZONA_SAMPLE_RATE_3_MASK ; 
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  CONFIG_OF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int WM5102_DIG_VU ; 
 int /*<<< orphan*/  WMFW_ADSP2 ; 
 int /*<<< orphan*/  arizona_free_irq (struct arizona*,int /*<<< orphan*/ ,struct wm5102_priv*) ; 
 int /*<<< orphan*/  arizona_free_spk_irqs (struct arizona*) ; 
 int /*<<< orphan*/  arizona_init_common (struct arizona*) ; 
 int /*<<< orphan*/  arizona_init_dai (TYPE_14__*,int) ; 
 int /*<<< orphan*/  arizona_init_dvfs (TYPE_14__*) ; 
 int /*<<< orphan*/  arizona_init_fll (struct arizona*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int arizona_init_spk_irqs (struct arizona*) ; 
 int arizona_init_vol_limit (struct arizona*) ; 
 int arizona_of_get_audio_pdata (struct arizona*) ; 
 int arizona_request_irq (struct arizona*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct wm5102_priv*) ; 
 int arizona_set_irq_wake (struct arizona*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,int) ; 
 struct arizona* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_6__*,char*,int) ; 
 struct wm5102_priv* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (TYPE_6__*,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm5102_priv*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_6__*) ; 
 int /*<<< orphan*/  pm_runtime_idle (TYPE_6__*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,TYPE_2__,int,int) ; 
 int /*<<< orphan*/  soc_component_dev_wm5102 ; 
 int /*<<< orphan*/  wm5102_adsp2_irq ; 
 TYPE_2__* wm5102_dai ; 
 TYPE_2__* wm5102_digital_vu ; 
 TYPE_2__* wm5102_dsp1_regions ; 
 int wm_adsp2_init (TYPE_1__*) ; 

__attribute__((used)) static int wm5102_probe(struct platform_device *pdev)
{
	struct arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	struct wm5102_priv *wm5102;
	int i, ret;

	wm5102 = devm_kzalloc(&pdev->dev, sizeof(struct wm5102_priv),
			      GFP_KERNEL);
	if (wm5102 == NULL)
		return -ENOMEM;
	platform_set_drvdata(pdev, wm5102);

	if (IS_ENABLED(CONFIG_OF)) {
		if (!dev_get_platdata(arizona->dev)) {
			ret = arizona_of_get_audio_pdata(arizona);
			if (ret < 0)
				return ret;
		}
	}

	mutex_init(&arizona->dac_comp_lock);

	wm5102->core.arizona = arizona;
	wm5102->core.num_inputs = 6;

	arizona_init_dvfs(&wm5102->core);

	wm5102->core.adsp[0].part = "wm5102";
	wm5102->core.adsp[0].num = 1;
	wm5102->core.adsp[0].type = WMFW_ADSP2;
	wm5102->core.adsp[0].base = ARIZONA_DSP1_CONTROL_1;
	wm5102->core.adsp[0].dev = arizona->dev;
	wm5102->core.adsp[0].regmap = arizona->regmap;
	wm5102->core.adsp[0].mem = wm5102_dsp1_regions;
	wm5102->core.adsp[0].num_mems = ARRAY_SIZE(wm5102_dsp1_regions);

	ret = wm_adsp2_init(&wm5102->core.adsp[0]);
	if (ret != 0)
		return ret;

	for (i = 0; i < ARRAY_SIZE(wm5102->fll); i++)
		wm5102->fll[i].vco_mult = 1;

	arizona_init_fll(arizona, 1, ARIZONA_FLL1_CONTROL_1 - 1,
			 ARIZONA_IRQ_FLL1_LOCK, ARIZONA_IRQ_FLL1_CLOCK_OK,
			 &wm5102->fll[0]);
	arizona_init_fll(arizona, 2, ARIZONA_FLL2_CONTROL_1 - 1,
			 ARIZONA_IRQ_FLL2_LOCK, ARIZONA_IRQ_FLL2_CLOCK_OK,
			 &wm5102->fll[1]);

	/* SR2 fixed at 8kHz, SR3 fixed at 16kHz */
	regmap_update_bits(arizona->regmap, ARIZONA_SAMPLE_RATE_2,
			   ARIZONA_SAMPLE_RATE_2_MASK, 0x11);
	regmap_update_bits(arizona->regmap, ARIZONA_SAMPLE_RATE_3,
			   ARIZONA_SAMPLE_RATE_3_MASK, 0x12);

	for (i = 0; i < ARRAY_SIZE(wm5102_dai); i++)
		arizona_init_dai(&wm5102->core, i);

	/* Latch volume update bits */
	for (i = 0; i < ARRAY_SIZE(wm5102_digital_vu); i++)
		regmap_update_bits(arizona->regmap, wm5102_digital_vu[i],
				   WM5102_DIG_VU, WM5102_DIG_VU);

	pm_runtime_enable(&pdev->dev);
	pm_runtime_idle(&pdev->dev);

	ret = arizona_request_irq(arizona, ARIZONA_IRQ_DSP_IRQ1,
				  "ADSP2 Compressed IRQ", wm5102_adsp2_irq,
				  wm5102);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to request DSP IRQ: %d\n", ret);
		return ret;
	}

	ret = arizona_set_irq_wake(arizona, ARIZONA_IRQ_DSP_IRQ1, 1);
	if (ret != 0)
		dev_warn(&pdev->dev,
			 "Failed to set compressed IRQ as a wake source: %d\n",
			 ret);

	arizona_init_common(arizona);

	ret = arizona_init_vol_limit(arizona);
	if (ret < 0)
		goto err_dsp_irq;
	ret = arizona_init_spk_irqs(arizona);
	if (ret < 0)
		goto err_dsp_irq;

	ret = devm_snd_soc_register_component(&pdev->dev,
					      &soc_component_dev_wm5102,
					      wm5102_dai,
					      ARRAY_SIZE(wm5102_dai));
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);
		goto err_spk_irqs;
	}

	return ret;

err_spk_irqs:
	arizona_free_spk_irqs(arizona);
err_dsp_irq:
	arizona_set_irq_wake(arizona, ARIZONA_IRQ_DSP_IRQ1, 0);
	arizona_free_irq(arizona, ARIZONA_IRQ_DSP_IRQ1, wm5102);

	return ret;
}