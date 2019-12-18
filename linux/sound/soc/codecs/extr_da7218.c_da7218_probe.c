#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {TYPE_1__* dev; } ;
struct da7218_priv {scalar_t__ dev_id; int /*<<< orphan*/  supplies; scalar_t__ irq; int /*<<< orphan*/ * mclk; int /*<<< orphan*/  pdata; } ;
struct TYPE_5__ {scalar_t__ of_node; } ;

/* Variables and functions */
 scalar_t__ DA7217_DEV_ID ; 
 int /*<<< orphan*/  DA7218_BEEP_CYCLES_MASK ; 
 int /*<<< orphan*/  DA7218_CP_CTRL ; 
 int /*<<< orphan*/  DA7218_CP_SMALL_SWITCH_FREQ_EN_MASK ; 
 int /*<<< orphan*/  DA7218_DGS_GAIN_CTRL ; 
 int /*<<< orphan*/  DA7218_DGS_RAMP_EN_MASK ; 
 int /*<<< orphan*/  DA7218_DROUTING_OUTFILT_1L ; 
 int /*<<< orphan*/  DA7218_DROUTING_OUTFILT_1R ; 
 int /*<<< orphan*/  DA7218_EVENT_MASK ; 
 int /*<<< orphan*/  DA7218_HPLDET_JACK_EVENT_IRQ_MSK_MASK ; 
 int /*<<< orphan*/  DA7218_HP_AMP_DIFF_MODE_EN_MASK ; 
 int /*<<< orphan*/  DA7218_HP_DIFF_CTRL ; 
 int /*<<< orphan*/  DA7218_HP_L_AMP_RAMP_EN_MASK ; 
 int /*<<< orphan*/  DA7218_HP_L_CTRL ; 
 int /*<<< orphan*/  DA7218_HP_R_AMP_RAMP_EN_MASK ; 
 int /*<<< orphan*/  DA7218_HP_R_CTRL ; 
 int /*<<< orphan*/  DA7218_IN_1L_FILTER_CTRL ; 
 int /*<<< orphan*/  DA7218_IN_1L_RAMP_EN_MASK ; 
 int /*<<< orphan*/  DA7218_IN_1R_FILTER_CTRL ; 
 int /*<<< orphan*/  DA7218_IN_1R_RAMP_EN_MASK ; 
 int /*<<< orphan*/  DA7218_IN_2L_FILTER_CTRL ; 
 int /*<<< orphan*/  DA7218_IN_2L_RAMP_EN_MASK ; 
 int /*<<< orphan*/  DA7218_IN_2R_FILTER_CTRL ; 
 int /*<<< orphan*/  DA7218_IN_2R_RAMP_EN_MASK ; 
 int /*<<< orphan*/  DA7218_MIXIN_1_AMP_RAMP_EN_MASK ; 
 int /*<<< orphan*/  DA7218_MIXIN_1_CTRL ; 
 int /*<<< orphan*/  DA7218_MIXIN_2_AMP_RAMP_EN_MASK ; 
 int /*<<< orphan*/  DA7218_MIXIN_2_CTRL ; 
 int /*<<< orphan*/  DA7218_NUM_SUPPLIES ; 
 int /*<<< orphan*/  DA7218_OUT_1L_FILTER_CTRL ; 
 int /*<<< orphan*/  DA7218_OUT_1L_RAMP_EN_MASK ; 
 int /*<<< orphan*/  DA7218_OUT_1R_FILTER_CTRL ; 
 int /*<<< orphan*/  DA7218_OUT_1R_RAMP_EN_MASK ; 
 int /*<<< orphan*/  DA7218_PC_COUNT ; 
 int /*<<< orphan*/  DA7218_PC_FREERUN_MASK ; 
 int /*<<< orphan*/  DA7218_TONE_GEN_CYCLES ; 
 int ENOENT ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da7218_handle_pdata (struct snd_soc_component*) ; 
 int da7218_handle_supplies (struct snd_soc_component*) ; 
 int /*<<< orphan*/  da7218_irq_thread ; 
 int /*<<< orphan*/  da7218_of_to_pdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/ * devm_clk_get (TYPE_1__*,char*) ; 
 int devm_request_threaded_irq (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct snd_soc_component*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da7218_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7218_probe(struct snd_soc_component *component)
{
	struct da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	int ret;

	/* Regulator configuration */
	ret = da7218_handle_supplies(component);
	if (ret)
		return ret;

	/* Handle DT/Platform data */
	if (component->dev->of_node)
		da7218->pdata = da7218_of_to_pdata(component);
	else
		da7218->pdata = dev_get_platdata(component->dev);

	da7218_handle_pdata(component);

	/* Check if MCLK provided, if not the clock is NULL */
	da7218->mclk = devm_clk_get(component->dev, "mclk");
	if (IS_ERR(da7218->mclk)) {
		if (PTR_ERR(da7218->mclk) != -ENOENT) {
			ret = PTR_ERR(da7218->mclk);
			goto err_disable_reg;
		} else {
			da7218->mclk = NULL;
		}
	}

	/* Default PC to free-running */
	snd_soc_component_write(component, DA7218_PC_COUNT, DA7218_PC_FREERUN_MASK);

	/*
	 * Default Output Filter mixers to off otherwise DAPM will power
	 * Mic to HP passthrough paths by default at startup.
	 */
	snd_soc_component_write(component, DA7218_DROUTING_OUTFILT_1L, 0);
	snd_soc_component_write(component, DA7218_DROUTING_OUTFILT_1R, 0);

	/* Default CP to normal load, power mode */
	snd_soc_component_update_bits(component, DA7218_CP_CTRL,
			    DA7218_CP_SMALL_SWITCH_FREQ_EN_MASK, 0);

	/* Default gain ramping */
	snd_soc_component_update_bits(component, DA7218_MIXIN_1_CTRL,
			    DA7218_MIXIN_1_AMP_RAMP_EN_MASK,
			    DA7218_MIXIN_1_AMP_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_MIXIN_2_CTRL,
			    DA7218_MIXIN_2_AMP_RAMP_EN_MASK,
			    DA7218_MIXIN_2_AMP_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_1L_FILTER_CTRL,
			    DA7218_IN_1L_RAMP_EN_MASK,
			    DA7218_IN_1L_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_1R_FILTER_CTRL,
			    DA7218_IN_1R_RAMP_EN_MASK,
			    DA7218_IN_1R_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_2L_FILTER_CTRL,
			    DA7218_IN_2L_RAMP_EN_MASK,
			    DA7218_IN_2L_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_IN_2R_FILTER_CTRL,
			    DA7218_IN_2R_RAMP_EN_MASK,
			    DA7218_IN_2R_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_DGS_GAIN_CTRL,
			    DA7218_DGS_RAMP_EN_MASK, DA7218_DGS_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_OUT_1L_FILTER_CTRL,
			    DA7218_OUT_1L_RAMP_EN_MASK,
			    DA7218_OUT_1L_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_OUT_1R_FILTER_CTRL,
			    DA7218_OUT_1R_RAMP_EN_MASK,
			    DA7218_OUT_1R_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_HP_L_CTRL,
			    DA7218_HP_L_AMP_RAMP_EN_MASK,
			    DA7218_HP_L_AMP_RAMP_EN_MASK);
	snd_soc_component_update_bits(component, DA7218_HP_R_CTRL,
			    DA7218_HP_R_AMP_RAMP_EN_MASK,
			    DA7218_HP_R_AMP_RAMP_EN_MASK);

	/* Default infinite tone gen, start/stop by Kcontrol */
	snd_soc_component_write(component, DA7218_TONE_GEN_CYCLES, DA7218_BEEP_CYCLES_MASK);

	/* DA7217 specific config */
	if (da7218->dev_id == DA7217_DEV_ID) {
		snd_soc_component_update_bits(component, DA7218_HP_DIFF_CTRL,
				    DA7218_HP_AMP_DIFF_MODE_EN_MASK,
				    DA7218_HP_AMP_DIFF_MODE_EN_MASK);

		/* Only DA7218 supports HP detect, mask off for DA7217 */
		snd_soc_component_write(component, DA7218_EVENT_MASK,
			      DA7218_HPLDET_JACK_EVENT_IRQ_MSK_MASK);
	}

	if (da7218->irq) {
		ret = devm_request_threaded_irq(component->dev, da7218->irq, NULL,
						da7218_irq_thread,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"da7218", component);
		if (ret != 0) {
			dev_err(component->dev, "Failed to request IRQ %d: %d\n",
				da7218->irq, ret);
			goto err_disable_reg;
		}

	}

	return 0;

err_disable_reg:
	regulator_bulk_disable(DA7218_NUM_SUPPLIES, da7218->supplies);

	return ret;
}