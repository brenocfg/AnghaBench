#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct madera {int /*<<< orphan*/  regmap; int /*<<< orphan*/  regmap_32bit; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_dev; } ;
struct TYPE_18__ {int num_inputs; TYPE_1__* adsp; TYPE_3__* dev; struct madera* madera; } ;
struct cs47l90 {TYPE_6__ core; int /*<<< orphan*/ * fll; } ;
struct TYPE_16__ {char* part; int num; int rev; int num_mems; int /*<<< orphan*/  lock_regions; int /*<<< orphan*/  mem; int /*<<< orphan*/  base; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CS47L90_DIG_VU ; 
 int CS47L90_NUM_ADSP ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MADERA_FLL1_CONTROL_1 ; 
 scalar_t__ MADERA_FLL2_CONTROL_1 ; 
 scalar_t__ MADERA_FLLAO_CONTROL_1 ; 
 int /*<<< orphan*/  MADERA_IRQ_DSP_IRQ1 ; 
 int MADERA_MAX_DAI ; 
 int /*<<< orphan*/  WMFW_ADSP2 ; 
 int /*<<< orphan*/  WM_ADSP2_REGION_1_9 ; 
 int /*<<< orphan*/  cs47l90_adsp2_irq ; 
 int /*<<< orphan*/ * cs47l90_dai ; 
 int /*<<< orphan*/ * cs47l90_digital_vu ; 
 int /*<<< orphan*/ * cs47l90_dsp1_regions ; 
 int /*<<< orphan*/ * cs47l90_dsp_control_bases ; 
 int /*<<< orphan*/ * cs47l90_dsp_regions ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 struct madera* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int) ; 
 struct cs47l90* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  madera_core_free (TYPE_6__*) ; 
 int madera_core_init (TYPE_6__*) ; 
 int /*<<< orphan*/  madera_free_bus_error_irq (TYPE_6__*,int) ; 
 int /*<<< orphan*/  madera_free_irq (struct madera*,int /*<<< orphan*/ ,struct cs47l90*) ; 
 int madera_init_bus_error_irq (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  madera_init_dai (TYPE_6__*,int) ; 
 int /*<<< orphan*/  madera_init_fll (struct madera*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int madera_request_irq (struct madera*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct cs47l90*) ; 
 int madera_set_irq_wake (struct madera*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cs47l90*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_idle (TYPE_3__*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_component_dev_cs47l90 ; 
 int /*<<< orphan*/  wm_adsp2_bus_error ; 
 int wm_adsp2_init (TYPE_1__*) ; 
 int /*<<< orphan*/  wm_adsp2_remove (TYPE_1__*) ; 

__attribute__((used)) static int cs47l90_probe(struct platform_device *pdev)
{
	struct madera *madera = dev_get_drvdata(pdev->dev.parent);
	struct cs47l90 *cs47l90;
	int i, ret;

	BUILD_BUG_ON(ARRAY_SIZE(cs47l90_dai) > MADERA_MAX_DAI);

	/* quick exit if Madera irqchip driver hasn't completed probe */
	if (!madera->irq_dev) {
		dev_dbg(&pdev->dev, "irqchip driver not ready\n");
		return -EPROBE_DEFER;
	}

	cs47l90 = devm_kzalloc(&pdev->dev, sizeof(struct cs47l90),
			       GFP_KERNEL);
	if (!cs47l90)
		return -ENOMEM;

	platform_set_drvdata(pdev, cs47l90);

	cs47l90->core.madera = madera;
	cs47l90->core.dev = &pdev->dev;
	cs47l90->core.num_inputs = 10;

	ret = madera_core_init(&cs47l90->core);
	if (ret)
		return ret;

	ret = madera_request_irq(madera, MADERA_IRQ_DSP_IRQ1,
				 "ADSP2 Compressed IRQ", cs47l90_adsp2_irq,
				 cs47l90);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to request DSP IRQ: %d\n", ret);
		goto error_core;
	}

	ret = madera_set_irq_wake(madera, MADERA_IRQ_DSP_IRQ1, 1);
	if (ret)
		dev_warn(&pdev->dev, "Failed to set DSP IRQ wake: %d\n", ret);

	for (i = 0; i < CS47L90_NUM_ADSP; i++) {
		cs47l90->core.adsp[i].part = "cs47l90";
		cs47l90->core.adsp[i].num = i + 1;
		cs47l90->core.adsp[i].type = WMFW_ADSP2;
		cs47l90->core.adsp[i].rev = 2;
		cs47l90->core.adsp[i].dev = madera->dev;
		cs47l90->core.adsp[i].regmap = madera->regmap_32bit;

		cs47l90->core.adsp[i].base = cs47l90_dsp_control_bases[i];
		cs47l90->core.adsp[i].mem = cs47l90_dsp_regions[i];
		cs47l90->core.adsp[i].num_mems =
			ARRAY_SIZE(cs47l90_dsp1_regions);

		cs47l90->core.adsp[i].lock_regions = WM_ADSP2_REGION_1_9;

		ret = wm_adsp2_init(&cs47l90->core.adsp[i]);

		if (ret == 0) {
			ret = madera_init_bus_error_irq(&cs47l90->core, i,
							wm_adsp2_bus_error);
			if (ret != 0)
				wm_adsp2_remove(&cs47l90->core.adsp[i]);
		}

		if (ret) {
			for (--i; i >= 0; --i) {
				madera_free_bus_error_irq(&cs47l90->core, i);
				wm_adsp2_remove(&cs47l90->core.adsp[i]);
			}
			goto error_dsp_irq;
		}
	}

	madera_init_fll(madera, 1, MADERA_FLL1_CONTROL_1 - 1,
			&cs47l90->fll[0]);
	madera_init_fll(madera, 2, MADERA_FLL2_CONTROL_1 - 1,
			&cs47l90->fll[1]);
	madera_init_fll(madera, 4, MADERA_FLLAO_CONTROL_1 - 1,
			&cs47l90->fll[2]);

	for (i = 0; i < ARRAY_SIZE(cs47l90_dai); i++)
		madera_init_dai(&cs47l90->core, i);

	/* Latch volume update bits */
	for (i = 0; i < ARRAY_SIZE(cs47l90_digital_vu); i++)
		regmap_update_bits(madera->regmap, cs47l90_digital_vu[i],
				   CS47L90_DIG_VU, CS47L90_DIG_VU);

	pm_runtime_enable(&pdev->dev);
	pm_runtime_idle(&pdev->dev);

	ret = devm_snd_soc_register_component(&pdev->dev,
					      &soc_component_dev_cs47l90,
					      cs47l90_dai,
					      ARRAY_SIZE(cs47l90_dai));
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);
		goto error_pm_runtime;
	}

	return ret;

error_pm_runtime:
	pm_runtime_disable(&pdev->dev);

	for (i = 0; i < CS47L90_NUM_ADSP; i++) {
		madera_free_bus_error_irq(&cs47l90->core, i);
		wm_adsp2_remove(&cs47l90->core.adsp[i]);
	}
error_dsp_irq:
	madera_set_irq_wake(madera, MADERA_IRQ_DSP_IRQ1, 0);
	madera_free_irq(madera, MADERA_IRQ_DSP_IRQ1, cs47l90);
error_core:
	madera_core_free(&cs47l90->core);

	return ret;
}