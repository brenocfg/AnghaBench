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
struct sta350_priv {int* coef_shadow; int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; struct sta350_platform_data* pdata; } ;
struct sta350_platform_data {int ffx_power_output_mode; int drop_compensation_ns; int output_conf; int ch1_output_mapping; int ch2_output_mapping; int ch3_output_mapping; int powerdown_delay_divider; scalar_t__ powerdown_master_vol; scalar_t__ noise_shape_dc_cut; scalar_t__ bridge_immediate_off; scalar_t__ activate_mute_output; scalar_t__ invalid_input_detect_mute; scalar_t__ distortion_compensation; scalar_t__ odd_pwm_speed_mode; scalar_t__ am_reduction_mode; scalar_t__ max_power_correction; scalar_t__ max_power_use_mpcc; scalar_t__ oc_warning_adjustment; int /*<<< orphan*/  fault_detect_recovery; int /*<<< orphan*/  thermal_warning_adjustment; int /*<<< orphan*/  thermal_warning_recovery; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  STA350_C1CFG ; 
 int /*<<< orphan*/  STA350_C2CFG ; 
 int /*<<< orphan*/  STA350_C3CFG ; 
 int /*<<< orphan*/  STA350_CONFA ; 
 int STA350_CONFA_FDRB ; 
 int STA350_CONFA_TWAB ; 
 int STA350_CONFA_TWRB ; 
 int /*<<< orphan*/  STA350_CONFC ; 
 int STA350_CONFC_CSZ_MASK ; 
 int STA350_CONFC_CSZ_SHIFT ; 
 int STA350_CONFC_OCRB ; 
 int STA350_CONFC_OM_MASK ; 
 int STA350_CONFC_OM_SHIFT ; 
 int /*<<< orphan*/  STA350_CONFE ; 
 int STA350_CONFE_AME ; 
 int STA350_CONFE_DCCV ; 
 int STA350_CONFE_MPC ; 
 int STA350_CONFE_MPCV ; 
 int STA350_CONFE_PWMS ; 
 int /*<<< orphan*/  STA350_CONFF ; 
 int STA350_CONFF_IDE ; 
 int STA350_CONFF_OCFG_MASK ; 
 int STA350_CONFF_OCFG_SHIFT ; 
 int STA350_CxCFG_OM_MASK ; 
 int STA350_CxCFG_OM_SHIFT ; 
 int /*<<< orphan*/  STA350_MISC1 ; 
 int STA350_MISC1_BRIDGOFF ; 
 int STA350_MISC1_CPWMEN ; 
 int STA350_MISC1_NSHHPEN ; 
 int STA350_MISC1_RPDNEN ; 
 int /*<<< orphan*/  STA350_MISC2 ; 
 int STA350_MISC2_PNDLSL_MASK ; 
 int STA350_MISC2_PNDLSL_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct sta350_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int sta350_startup_sequence (struct sta350_priv*) ; 

__attribute__((used)) static int sta350_probe(struct snd_soc_component *component)
{
	struct sta350_priv *sta350 = snd_soc_component_get_drvdata(component);
	struct sta350_platform_data *pdata = sta350->pdata;
	int i, ret = 0, thermal = 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(sta350->supplies),
				    sta350->supplies);
	if (ret < 0) {
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	ret = sta350_startup_sequence(sta350);
	if (ret < 0) {
		dev_err(component->dev, "Failed to startup device\n");
		return ret;
	}

	/* CONFA */
	if (!pdata->thermal_warning_recovery)
		thermal |= STA350_CONFA_TWAB;
	if (!pdata->thermal_warning_adjustment)
		thermal |= STA350_CONFA_TWRB;
	if (!pdata->fault_detect_recovery)
		thermal |= STA350_CONFA_FDRB;
	regmap_update_bits(sta350->regmap, STA350_CONFA,
			   STA350_CONFA_TWAB | STA350_CONFA_TWRB |
			   STA350_CONFA_FDRB,
			   thermal);

	/* CONFC */
	regmap_update_bits(sta350->regmap, STA350_CONFC,
			   STA350_CONFC_OM_MASK,
			   pdata->ffx_power_output_mode
				<< STA350_CONFC_OM_SHIFT);
	regmap_update_bits(sta350->regmap, STA350_CONFC,
			   STA350_CONFC_CSZ_MASK,
			   pdata->drop_compensation_ns
				<< STA350_CONFC_CSZ_SHIFT);
	regmap_update_bits(sta350->regmap,
			   STA350_CONFC,
			   STA350_CONFC_OCRB,
			   pdata->oc_warning_adjustment ?
				STA350_CONFC_OCRB : 0);

	/* CONFE */
	regmap_update_bits(sta350->regmap, STA350_CONFE,
			   STA350_CONFE_MPCV,
			   pdata->max_power_use_mpcc ?
				STA350_CONFE_MPCV : 0);
	regmap_update_bits(sta350->regmap, STA350_CONFE,
			   STA350_CONFE_MPC,
			   pdata->max_power_correction ?
				STA350_CONFE_MPC : 0);
	regmap_update_bits(sta350->regmap, STA350_CONFE,
			   STA350_CONFE_AME,
			   pdata->am_reduction_mode ?
				STA350_CONFE_AME : 0);
	regmap_update_bits(sta350->regmap, STA350_CONFE,
			   STA350_CONFE_PWMS,
			   pdata->odd_pwm_speed_mode ?
				STA350_CONFE_PWMS : 0);
	regmap_update_bits(sta350->regmap, STA350_CONFE,
			   STA350_CONFE_DCCV,
			   pdata->distortion_compensation ?
				STA350_CONFE_DCCV : 0);
	/*  CONFF */
	regmap_update_bits(sta350->regmap, STA350_CONFF,
			   STA350_CONFF_IDE,
			   pdata->invalid_input_detect_mute ?
				STA350_CONFF_IDE : 0);
	regmap_update_bits(sta350->regmap, STA350_CONFF,
			   STA350_CONFF_OCFG_MASK,
			   pdata->output_conf
				<< STA350_CONFF_OCFG_SHIFT);

	/* channel to output mapping */
	regmap_update_bits(sta350->regmap, STA350_C1CFG,
			   STA350_CxCFG_OM_MASK,
			   pdata->ch1_output_mapping
				<< STA350_CxCFG_OM_SHIFT);
	regmap_update_bits(sta350->regmap, STA350_C2CFG,
			   STA350_CxCFG_OM_MASK,
			   pdata->ch2_output_mapping
				<< STA350_CxCFG_OM_SHIFT);
	regmap_update_bits(sta350->regmap, STA350_C3CFG,
			   STA350_CxCFG_OM_MASK,
			   pdata->ch3_output_mapping
				<< STA350_CxCFG_OM_SHIFT);

	/* miscellaneous registers */
	regmap_update_bits(sta350->regmap, STA350_MISC1,
			   STA350_MISC1_CPWMEN,
			   pdata->activate_mute_output ?
				STA350_MISC1_CPWMEN : 0);
	regmap_update_bits(sta350->regmap, STA350_MISC1,
			   STA350_MISC1_BRIDGOFF,
			   pdata->bridge_immediate_off ?
				STA350_MISC1_BRIDGOFF : 0);
	regmap_update_bits(sta350->regmap, STA350_MISC1,
			   STA350_MISC1_NSHHPEN,
			   pdata->noise_shape_dc_cut ?
				STA350_MISC1_NSHHPEN : 0);
	regmap_update_bits(sta350->regmap, STA350_MISC1,
			   STA350_MISC1_RPDNEN,
			   pdata->powerdown_master_vol ?
				STA350_MISC1_RPDNEN: 0);

	regmap_update_bits(sta350->regmap, STA350_MISC2,
			   STA350_MISC2_PNDLSL_MASK,
			   pdata->powerdown_delay_divider
				<< STA350_MISC2_PNDLSL_SHIFT);

	/* initialize coefficient shadow RAM with reset values */
	for (i = 4; i <= 49; i += 5)
		sta350->coef_shadow[i] = 0x400000;
	for (i = 50; i <= 54; i++)
		sta350->coef_shadow[i] = 0x7fffff;
	sta350->coef_shadow[55] = 0x5a9df7;
	sta350->coef_shadow[56] = 0x7fffff;
	sta350->coef_shadow[59] = 0x7fffff;
	sta350->coef_shadow[60] = 0x400000;
	sta350->coef_shadow[61] = 0x400000;

	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_STANDBY);
	/* Bias level configuration will have done an extra enable */
	regulator_bulk_disable(ARRAY_SIZE(sta350->supplies), sta350->supplies);

	return 0;
}