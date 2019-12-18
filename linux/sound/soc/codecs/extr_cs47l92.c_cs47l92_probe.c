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
struct cs47l92 {TYPE_6__ core; int /*<<< orphan*/ * fll; } ;
struct TYPE_16__ {char* part; int num; int rev; int num_mems; int /*<<< orphan*/  lock_regions; int /*<<< orphan*/ * mem; int /*<<< orphan*/  base; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CS47L92_DIG_VU ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MADERA_DSP1_CONFIG_1 ; 
 scalar_t__ MADERA_FLL1_CONTROL_1 ; 
 scalar_t__ MADERA_FLL2_CONTROL_1 ; 
 int /*<<< orphan*/  MADERA_IRQ_DSP_IRQ1 ; 
 int MADERA_MAX_DAI ; 
 int /*<<< orphan*/  WMFW_ADSP2 ; 
 int /*<<< orphan*/  WM_ADSP2_REGION_1_9 ; 
 int /*<<< orphan*/  cs47l92_adsp2_irq ; 
 int /*<<< orphan*/ * cs47l92_dai ; 
 int /*<<< orphan*/ * cs47l92_digital_vu ; 
 int /*<<< orphan*/ * cs47l92_dsp1_regions ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 struct madera* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int) ; 
 struct cs47l92* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  madera_core_free (TYPE_6__*) ; 
 int madera_core_init (TYPE_6__*) ; 
 int /*<<< orphan*/  madera_free_bus_error_irq (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  madera_free_irq (struct madera*,int /*<<< orphan*/ ,struct cs47l92*) ; 
 int madera_init_bus_error_irq (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  madera_init_dai (TYPE_6__*,int) ; 
 int /*<<< orphan*/  madera_init_fll (struct madera*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int madera_request_irq (struct madera*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct cs47l92*) ; 
 int madera_set_irq_wake (struct madera*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cs47l92*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_idle (TYPE_3__*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_component_dev_cs47l92 ; 
 int /*<<< orphan*/  wm_adsp2_bus_error ; 
 int wm_adsp2_init (TYPE_1__*) ; 
 int /*<<< orphan*/  wm_adsp2_remove (TYPE_1__*) ; 

__attribute__((used)) static int cs47l92_probe(struct platform_device *pdev)
{
	struct madera *madera = dev_get_drvdata(pdev->dev.parent);
	struct cs47l92 *cs47l92;
	int i, ret;

	BUILD_BUG_ON(ARRAY_SIZE(cs47l92_dai) > MADERA_MAX_DAI);

	/* quick exit if Madera irqchip driver hasn't completed probe */
	if (!madera->irq_dev) {
		dev_dbg(&pdev->dev, "irqchip driver not ready\n");
		return -EPROBE_DEFER;
	}

	cs47l92 = devm_kzalloc(&pdev->dev, sizeof(struct cs47l92), GFP_KERNEL);
	if (!cs47l92)
		return -ENOMEM;

	platform_set_drvdata(pdev, cs47l92);

	cs47l92->core.madera = madera;
	cs47l92->core.dev = &pdev->dev;
	cs47l92->core.num_inputs = 8;

	ret = madera_core_init(&cs47l92->core);
	if (ret)
		return ret;

	ret = madera_request_irq(madera, MADERA_IRQ_DSP_IRQ1,
				 "ADSP2 Compressed IRQ", cs47l92_adsp2_irq,
				 cs47l92);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to request DSP IRQ: %d\n", ret);
		goto error_core;
	}

	ret = madera_set_irq_wake(madera, MADERA_IRQ_DSP_IRQ1, 1);
	if (ret)
		dev_warn(&pdev->dev, "Failed to set DSP IRQ wake: %d\n", ret);

	cs47l92->core.adsp[0].part = "cs47l92";
	cs47l92->core.adsp[0].num = 1;
	cs47l92->core.adsp[0].type = WMFW_ADSP2;
	cs47l92->core.adsp[0].rev = 2;
	cs47l92->core.adsp[0].dev = madera->dev;
	cs47l92->core.adsp[0].regmap = madera->regmap_32bit;

	cs47l92->core.adsp[0].base = MADERA_DSP1_CONFIG_1;
	cs47l92->core.adsp[0].mem = cs47l92_dsp1_regions;
	cs47l92->core.adsp[0].num_mems = ARRAY_SIZE(cs47l92_dsp1_regions);

	cs47l92->core.adsp[0].lock_regions = WM_ADSP2_REGION_1_9;

	ret = wm_adsp2_init(&cs47l92->core.adsp[0]);
	if (ret != 0)
		goto error_dsp_irq;

	ret = madera_init_bus_error_irq(&cs47l92->core, 0, wm_adsp2_bus_error);
	if (ret != 0) {
		wm_adsp2_remove(&cs47l92->core.adsp[0]);
		goto error_adsp;
	}

	madera_init_fll(madera, 1, MADERA_FLL1_CONTROL_1 - 1,
			&cs47l92->fll[0]);
	madera_init_fll(madera, 2, MADERA_FLL2_CONTROL_1 - 1,
			&cs47l92->fll[1]);

	for (i = 0; i < ARRAY_SIZE(cs47l92_dai); i++)
		madera_init_dai(&cs47l92->core, i);

	/* Latch volume update bits */
	for (i = 0; i < ARRAY_SIZE(cs47l92_digital_vu); i++)
		regmap_update_bits(madera->regmap, cs47l92_digital_vu[i],
				   CS47L92_DIG_VU, CS47L92_DIG_VU);

	pm_runtime_enable(&pdev->dev);
	pm_runtime_idle(&pdev->dev);

	ret = devm_snd_soc_register_component(&pdev->dev,
					      &soc_component_dev_cs47l92,
					      cs47l92_dai,
					      ARRAY_SIZE(cs47l92_dai));
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);
		goto error_pm_runtime;
	}

	return ret;

error_pm_runtime:
	pm_runtime_disable(&pdev->dev);
	madera_free_bus_error_irq(&cs47l92->core, 0);
error_adsp:
	wm_adsp2_remove(&cs47l92->core.adsp[0]);
error_dsp_irq:
	madera_set_irq_wake(madera, MADERA_IRQ_DSP_IRQ1, 0);
	madera_free_irq(madera, MADERA_IRQ_DSP_IRQ1, cs47l92);
error_core:
	madera_core_free(&cs47l92->core);

	return ret;
}