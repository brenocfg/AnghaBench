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
struct snd_soc_component {int dummy; } ;
struct da732x_priv {int pll_en; int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int DA732X_AUXL_ZC_EN ; 
 int DA732X_AUXR_ZC_EN ; 
 int /*<<< orphan*/  DA732X_BIAS_BOOST_100PC ; 
 int /*<<< orphan*/  DA732X_BIAS_BOOST_50PC ; 
 int DA732X_BIAS_BOOST_MASK ; 
 int /*<<< orphan*/  DA732X_BIAS_DIS ; 
 int DA732X_BIAS_EN ; 
 int DA732X_BYPASS_DSP ; 
 int DA732X_DIGITAL_EN ; 
 int /*<<< orphan*/  DA732X_DISABLE_CP ; 
 int /*<<< orphan*/  DA732X_ENABLE_CP ; 
 int DA732X_HPL_ZC_EN ; 
 int DA732X_HPR_ZC_EN ; 
 int DA732X_HP_DRIVER_EN ; 
 int DA732X_HP_GATE_LOW ; 
 int DA732X_HP_LOOP_GAIN_CTRL ; 
 int DA732X_HP_OUT_GNDSEL ; 
 int DA732X_LIN2_ZC_EN ; 
 int DA732X_LIN3_ZC_EN ; 
 int DA732X_LIN4_ZC_EN ; 
 int DA732X_MIC1_PRE_ZC_EN ; 
 int DA732X_MIC1_ZC_EN ; 
 int DA732X_MIC2_PRE_ZC_EN ; 
 int DA732X_MIC2_ZC_EN ; 
 int DA732X_MIC3_PRE_ZC_EN ; 
 int DA732X_MIC3_ZC_EN ; 
 int DA732X_PC_CLK_EN ; 
 int DA732X_PLL_EN ; 
 int DA732X_REFBUFX2_EN ; 
 int /*<<< orphan*/  DA732X_REG_BIAS_EN ; 
 int /*<<< orphan*/  DA732X_REG_CLK_EN1 ; 
 int /*<<< orphan*/  DA732X_REG_DATA_ROUTE ; 
 int /*<<< orphan*/  DA732X_REG_DSP_CTRL ; 
 int /*<<< orphan*/  DA732X_REG_HP_LIN1_GNDSEL ; 
 int /*<<< orphan*/  DA732X_REG_INP_ZC_EN ; 
 int /*<<< orphan*/  DA732X_REG_OUT_ZC_EN ; 
 int /*<<< orphan*/  DA732X_REG_PLL_CTRL ; 
 int /*<<< orphan*/  DA732X_REG_REF1 ; 
 int /*<<< orphan*/  DA732X_REG_SPARE1_OUT ; 
 int /*<<< orphan*/  DA732X_STARTUP_DELAY ; 
 int DA732X_SYS3_CLK_EN ; 
 int DA732X_VMID_FASTCHG ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  da732x_hp_dc_offset_cancellation (struct snd_soc_component*) ; 
 int /*<<< orphan*/  da732x_set_charge_pump (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct da732x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int da732x_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct da732x_priv *da732x = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, DA732X_REG_BIAS_EN,
				    DA732X_BIAS_BOOST_MASK,
				    DA732X_BIAS_BOOST_100PC);
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			/* Init Codec */
			snd_soc_component_write(component, DA732X_REG_REF1,
				      DA732X_VMID_FASTCHG);
			snd_soc_component_write(component, DA732X_REG_BIAS_EN,
				      DA732X_BIAS_EN);

			mdelay(DA732X_STARTUP_DELAY);

			/* Disable Fast Charge and enable DAC ref voltage */
			snd_soc_component_write(component, DA732X_REG_REF1,
				      DA732X_REFBUFX2_EN);

			/* Enable bypass DSP routing */
			snd_soc_component_write(component, DA732X_REG_DATA_ROUTE,
				      DA732X_BYPASS_DSP);

			/* Enable Digital subsystem */
			snd_soc_component_write(component, DA732X_REG_DSP_CTRL,
				      DA732X_DIGITAL_EN);

			snd_soc_component_write(component, DA732X_REG_SPARE1_OUT,
				      DA732X_HP_DRIVER_EN |
				      DA732X_HP_GATE_LOW |
				      DA732X_HP_LOOP_GAIN_CTRL);
			snd_soc_component_write(component, DA732X_REG_HP_LIN1_GNDSEL,
				      DA732X_HP_OUT_GNDSEL);

			da732x_set_charge_pump(component, DA732X_ENABLE_CP);

			snd_soc_component_write(component, DA732X_REG_CLK_EN1,
			      DA732X_SYS3_CLK_EN | DA732X_PC_CLK_EN);

			/* Enable Zero Crossing */
			snd_soc_component_write(component, DA732X_REG_INP_ZC_EN,
				      DA732X_MIC1_PRE_ZC_EN |
				      DA732X_MIC1_ZC_EN |
				      DA732X_MIC2_PRE_ZC_EN |
				      DA732X_MIC2_ZC_EN |
				      DA732X_AUXL_ZC_EN |
				      DA732X_AUXR_ZC_EN |
				      DA732X_MIC3_PRE_ZC_EN |
				      DA732X_MIC3_ZC_EN);
			snd_soc_component_write(component, DA732X_REG_OUT_ZC_EN,
				      DA732X_HPL_ZC_EN | DA732X_HPR_ZC_EN |
				      DA732X_LIN2_ZC_EN | DA732X_LIN3_ZC_EN |
				      DA732X_LIN4_ZC_EN);

			da732x_hp_dc_offset_cancellation(component);

			regcache_cache_only(da732x->regmap, false);
			regcache_sync(da732x->regmap);
		} else {
			snd_soc_component_update_bits(component, DA732X_REG_BIAS_EN,
					    DA732X_BIAS_BOOST_MASK,
					    DA732X_BIAS_BOOST_50PC);
			snd_soc_component_update_bits(component, DA732X_REG_PLL_CTRL,
					    DA732X_PLL_EN, 0);
			da732x->pll_en = false;
		}
		break;
	case SND_SOC_BIAS_OFF:
		regcache_cache_only(da732x->regmap, true);
		da732x_set_charge_pump(component, DA732X_DISABLE_CP);
		snd_soc_component_update_bits(component, DA732X_REG_BIAS_EN, DA732X_BIAS_EN,
				    DA732X_BIAS_DIS);
		da732x->pll_en = false;
		break;
	}

	return 0;
}