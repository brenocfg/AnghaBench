#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sta32x_priv {int* coef_shadow; int /*<<< orphan*/  supplies; int /*<<< orphan*/  watchdog_work; struct sta32x_platform_data* pdata; int /*<<< orphan*/  regmap; scalar_t__ xti_clk; struct snd_soc_component* component; } ;
struct sta32x_platform_data {int drop_compensation_ns; int output_conf; int ch1_output_mapping; int ch2_output_mapping; int ch3_output_mapping; scalar_t__ needs_esd_watchdog; scalar_t__ invalid_input_detect_mute; scalar_t__ odd_pwm_speed_mode; scalar_t__ am_reduction_mode; scalar_t__ max_power_correction; scalar_t__ max_power_use_mpcc; int /*<<< orphan*/  fault_detect_recovery; int /*<<< orphan*/  thermal_warning_adjustment; int /*<<< orphan*/  thermal_warning_recovery; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  STA32X_C1CFG ; 
 int /*<<< orphan*/  STA32X_C2CFG ; 
 int /*<<< orphan*/  STA32X_C3CFG ; 
 int /*<<< orphan*/  STA32X_CONFA ; 
 int STA32X_CONFA_FDRB ; 
 int STA32X_CONFA_TWAB ; 
 int STA32X_CONFA_TWRB ; 
 int /*<<< orphan*/  STA32X_CONFC ; 
 int STA32X_CONFC_CSZ_MASK ; 
 int STA32X_CONFC_CSZ_SHIFT ; 
 int /*<<< orphan*/  STA32X_CONFE ; 
 int STA32X_CONFE_AME ; 
 int STA32X_CONFE_MPC ; 
 int STA32X_CONFE_MPCV ; 
 int STA32X_CONFE_PWMS ; 
 int /*<<< orphan*/  STA32X_CONFF ; 
 int STA32X_CONFF_IDE ; 
 int STA32X_CONFF_OCFG_MASK ; 
 int STA32X_CONFF_OCFG_SHIFT ; 
 int STA32X_CxCFG_OM_MASK ; 
 int STA32X_CxCFG_OM_SHIFT ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct sta32x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int sta32x_startup_sequence (struct sta32x_priv*) ; 
 int /*<<< orphan*/  sta32x_watchdog ; 

__attribute__((used)) static int sta32x_probe(struct snd_soc_component *component)
{
	struct sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);
	struct sta32x_platform_data *pdata = sta32x->pdata;
	int i, ret = 0, thermal = 0;

	sta32x->component = component;

	if (sta32x->xti_clk) {
		ret = clk_prepare_enable(sta32x->xti_clk);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to enable clock: %d\n", ret);
			return ret;
		}
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(sta32x->supplies),
				    sta32x->supplies);
	if (ret != 0) {
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	ret = sta32x_startup_sequence(sta32x);
	if (ret < 0) {
		dev_err(component->dev, "Failed to startup device\n");
		return ret;
	}

	/* CONFA */
	if (!pdata->thermal_warning_recovery)
		thermal |= STA32X_CONFA_TWAB;
	if (!pdata->thermal_warning_adjustment)
		thermal |= STA32X_CONFA_TWRB;
	if (!pdata->fault_detect_recovery)
		thermal |= STA32X_CONFA_FDRB;
	regmap_update_bits(sta32x->regmap, STA32X_CONFA,
			   STA32X_CONFA_TWAB | STA32X_CONFA_TWRB |
			   STA32X_CONFA_FDRB,
			   thermal);

	/* CONFC */
	regmap_update_bits(sta32x->regmap, STA32X_CONFC,
			   STA32X_CONFC_CSZ_MASK,
			   pdata->drop_compensation_ns
				<< STA32X_CONFC_CSZ_SHIFT);

	/* CONFE */
	regmap_update_bits(sta32x->regmap, STA32X_CONFE,
			   STA32X_CONFE_MPCV,
			   pdata->max_power_use_mpcc ?
				STA32X_CONFE_MPCV : 0);
	regmap_update_bits(sta32x->regmap, STA32X_CONFE,
			   STA32X_CONFE_MPC,
			   pdata->max_power_correction ?
				STA32X_CONFE_MPC : 0);
	regmap_update_bits(sta32x->regmap, STA32X_CONFE,
			   STA32X_CONFE_AME,
			   pdata->am_reduction_mode ?
				STA32X_CONFE_AME : 0);
	regmap_update_bits(sta32x->regmap, STA32X_CONFE,
			   STA32X_CONFE_PWMS,
			   pdata->odd_pwm_speed_mode ?
				STA32X_CONFE_PWMS : 0);

	/*  CONFF */
	regmap_update_bits(sta32x->regmap, STA32X_CONFF,
			   STA32X_CONFF_IDE,
			   pdata->invalid_input_detect_mute ?
				STA32X_CONFF_IDE : 0);

	/* select output configuration  */
	regmap_update_bits(sta32x->regmap, STA32X_CONFF,
			   STA32X_CONFF_OCFG_MASK,
			   pdata->output_conf
				<< STA32X_CONFF_OCFG_SHIFT);

	/* channel to output mapping */
	regmap_update_bits(sta32x->regmap, STA32X_C1CFG,
			   STA32X_CxCFG_OM_MASK,
			   pdata->ch1_output_mapping
				<< STA32X_CxCFG_OM_SHIFT);
	regmap_update_bits(sta32x->regmap, STA32X_C2CFG,
			   STA32X_CxCFG_OM_MASK,
			   pdata->ch2_output_mapping
				<< STA32X_CxCFG_OM_SHIFT);
	regmap_update_bits(sta32x->regmap, STA32X_C3CFG,
			   STA32X_CxCFG_OM_MASK,
			   pdata->ch3_output_mapping
				<< STA32X_CxCFG_OM_SHIFT);

	/* initialize coefficient shadow RAM with reset values */
	for (i = 4; i <= 49; i += 5)
		sta32x->coef_shadow[i] = 0x400000;
	for (i = 50; i <= 54; i++)
		sta32x->coef_shadow[i] = 0x7fffff;
	sta32x->coef_shadow[55] = 0x5a9df7;
	sta32x->coef_shadow[56] = 0x7fffff;
	sta32x->coef_shadow[59] = 0x7fffff;
	sta32x->coef_shadow[60] = 0x400000;
	sta32x->coef_shadow[61] = 0x400000;

	if (sta32x->pdata->needs_esd_watchdog)
		INIT_DELAYED_WORK(&sta32x->watchdog_work, sta32x_watchdog);

	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_STANDBY);
	/* Bias level configuration will have done an extra enable */
	regulator_bulk_disable(ARRAY_SIZE(sta32x->supplies), sta32x->supplies);

	return 0;
}