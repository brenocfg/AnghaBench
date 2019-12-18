#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct madera {int /*<<< orphan*/  regmap; int /*<<< orphan*/  regmap_32bit; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_dev; } ;
struct TYPE_20__ {int num_inputs; TYPE_1__* adsp; TYPE_3__* dev; struct madera* madera; } ;
struct cs47l15 {TYPE_6__ core; int /*<<< orphan*/ * fll; } ;
struct TYPE_18__ {char* part; int num; int rev; int num_mems; int lock_regions; int /*<<< orphan*/ * mem; int /*<<< orphan*/  base; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CS47L15_DIG_VU ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MADERA_DSP1_CONFIG_1 ; 
 scalar_t__ MADERA_FLL1_CONTROL_1 ; 
 scalar_t__ MADERA_FLLAO_CONTROL_1 ; 
 int /*<<< orphan*/  MADERA_IRQ_DSP_IRQ1 ; 
 int MADERA_MAX_DAI ; 
 int /*<<< orphan*/  WMFW_ADSP2 ; 
 int WM_ADSP2_REGION_1 ; 
 int WM_ADSP2_REGION_2 ; 
 int WM_ADSP2_REGION_3 ; 
 int /*<<< orphan*/  cs47l15_adsp2_irq ; 
 int /*<<< orphan*/ * cs47l15_dai ; 
 int /*<<< orphan*/ * cs47l15_digital_vu ; 
 int /*<<< orphan*/ * cs47l15_dsp1_regions ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 struct madera* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int) ; 
 struct cs47l15* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  madera_core_free (TYPE_6__*) ; 
 int madera_core_init (TYPE_6__*) ; 
 int /*<<< orphan*/  madera_free_bus_error_irq (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  madera_free_irq (struct madera*,int /*<<< orphan*/ ,struct cs47l15*) ; 
 int /*<<< orphan*/  madera_free_overheat (TYPE_6__*) ; 
 int madera_init_bus_error_irq (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  madera_init_dai (TYPE_6__*,int) ; 
 int /*<<< orphan*/  madera_init_fll (struct madera*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int madera_init_overheat (TYPE_6__*) ; 
 int madera_request_irq (struct madera*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct cs47l15*) ; 
 int madera_set_irq_wake (struct madera*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cs47l15*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_idle (TYPE_3__*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_component_dev_cs47l15 ; 
 int /*<<< orphan*/  wm_adsp2_bus_error ; 
 int wm_adsp2_init (TYPE_1__*) ; 
 int /*<<< orphan*/  wm_adsp2_remove (TYPE_1__*) ; 

__attribute__((used)) static int cs47l15_probe(struct platform_device *pdev)
{
	struct madera *madera = dev_get_drvdata(pdev->dev.parent);
	struct cs47l15 *cs47l15;
	int i, ret;

	BUILD_BUG_ON(ARRAY_SIZE(cs47l15_dai) > MADERA_MAX_DAI);

	/* quick exit if Madera irqchip driver hasn't completed probe */
	if (!madera->irq_dev) {
		dev_dbg(&pdev->dev, "irqchip driver not ready\n");
		return -EPROBE_DEFER;
	}

	cs47l15 = devm_kzalloc(&pdev->dev, sizeof(struct cs47l15),
			       GFP_KERNEL);
	if (!cs47l15)
		return -ENOMEM;

	platform_set_drvdata(pdev, cs47l15);

	cs47l15->core.madera = madera;
	cs47l15->core.dev = &pdev->dev;
	cs47l15->core.num_inputs = 4;

	ret = madera_core_init(&cs47l15->core);
	if (ret)
		return ret;

	ret = madera_init_overheat(&cs47l15->core);
	if (ret)
		goto error_core;

	ret = madera_request_irq(madera, MADERA_IRQ_DSP_IRQ1,
				 "ADSP2 Compressed IRQ", cs47l15_adsp2_irq,
				 cs47l15);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to request DSP IRQ: %d\n", ret);
		goto error_overheat;
	}

	ret = madera_set_irq_wake(madera, MADERA_IRQ_DSP_IRQ1, 1);
	if (ret)
		dev_warn(&pdev->dev, "Failed to set DSP IRQ wake: %d\n", ret);

	cs47l15->core.adsp[0].part = "cs47l15";
	cs47l15->core.adsp[0].num = 1;
	cs47l15->core.adsp[0].type = WMFW_ADSP2;
	cs47l15->core.adsp[0].rev = 2;
	cs47l15->core.adsp[0].dev = madera->dev;
	cs47l15->core.adsp[0].regmap = madera->regmap_32bit;

	cs47l15->core.adsp[0].base = MADERA_DSP1_CONFIG_1;
	cs47l15->core.adsp[0].mem = cs47l15_dsp1_regions;
	cs47l15->core.adsp[0].num_mems = ARRAY_SIZE(cs47l15_dsp1_regions);

	cs47l15->core.adsp[0].lock_regions =
		WM_ADSP2_REGION_1 | WM_ADSP2_REGION_2 | WM_ADSP2_REGION_3;

	ret = wm_adsp2_init(&cs47l15->core.adsp[0]);
	if (ret != 0)
		goto error_dsp_irq;

	ret = madera_init_bus_error_irq(&cs47l15->core, 0, wm_adsp2_bus_error);
	if (ret)
		goto error_adsp;

	madera_init_fll(madera, 1, MADERA_FLL1_CONTROL_1 - 1,
			&cs47l15->fll[0]);
	madera_init_fll(madera, 4, MADERA_FLLAO_CONTROL_1 - 1,
			&cs47l15->fll[1]);

	for (i = 0; i < ARRAY_SIZE(cs47l15_dai); i++)
		madera_init_dai(&cs47l15->core, i);

	/* Latch volume update bits */
	for (i = 0; i < ARRAY_SIZE(cs47l15_digital_vu); i++)
		regmap_update_bits(madera->regmap, cs47l15_digital_vu[i],
				   CS47L15_DIG_VU, CS47L15_DIG_VU);

	pm_runtime_enable(&pdev->dev);
	pm_runtime_idle(&pdev->dev);

	ret = devm_snd_soc_register_component(&pdev->dev,
					      &soc_component_dev_cs47l15,
					      cs47l15_dai,
					      ARRAY_SIZE(cs47l15_dai));
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);
		goto error_pm_runtime;
	}

	return ret;

error_pm_runtime:
	pm_runtime_disable(&pdev->dev);
	madera_free_bus_error_irq(&cs47l15->core, 0);
error_adsp:
	wm_adsp2_remove(&cs47l15->core.adsp[0]);
error_dsp_irq:
	madera_set_irq_wake(madera, MADERA_IRQ_DSP_IRQ1, 0);
	madera_free_irq(madera, MADERA_IRQ_DSP_IRQ1, cs47l15);
error_overheat:
	madera_free_overheat(&cs47l15->core);
error_core:
	madera_core_free(&cs47l15->core);

	return ret;
}