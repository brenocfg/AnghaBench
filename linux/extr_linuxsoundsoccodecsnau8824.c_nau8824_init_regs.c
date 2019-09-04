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
struct regmap {int dummy; } ;
struct nau8824 {int vref_impedance; int micbias_voltage; int jack_eject_debounce; scalar_t__ sar_threshold_num; scalar_t__ jkdet_polarity; struct regmap* regmap; } ;

/* Variables and functions */
 int NAU8824_ADC_CH0_EN ; 
 int NAU8824_ADC_CH1_EN ; 
 int NAU8824_ADC_CH2_EN ; 
 int NAU8824_ADC_CH3_EN ; 
 int NAU8824_ADC_SYNC_DOWN_64 ; 
 int NAU8824_ADC_SYNC_DOWN_MASK ; 
 int NAU8824_CLASSG_TIMER_MASK ; 
 int NAU8824_CLASSG_TIMER_SFT ; 
 int NAU8824_CLK_ADC_CH01_EN ; 
 int NAU8824_CLK_ADC_CH23_EN ; 
 int NAU8824_CLK_ADC_SRC_MASK ; 
 int NAU8824_CLK_ADC_SRC_SFT ; 
 int NAU8824_CLK_DAC_CH0_EN ; 
 int NAU8824_CLK_DAC_CH1_EN ; 
 int NAU8824_CLK_DAC_SRC_MASK ; 
 int NAU8824_CLK_DAC_SRC_SFT ; 
 int NAU8824_CLK_DMIC_CH23_EN ; 
 int NAU8824_CLK_GAIN_EN ; 
 int NAU8824_CLK_I2S_EN ; 
 int NAU8824_CLK_SAR_EN ; 
 int NAU8824_DACL_HPL_EN ; 
 int NAU8824_DACR_HPR_EN ; 
 int NAU8824_DAC_CH0_EN ; 
 int NAU8824_DAC_CH0_SEL_I2S0 ; 
 int NAU8824_DAC_CH0_SEL_MASK ; 
 int NAU8824_DAC_CH1_EN ; 
 int NAU8824_DAC_CH1_SEL_I2S1 ; 
 int NAU8824_DAC_CH1_SEL_MASK ; 
 int NAU8824_DAC_CICCLP_OFF ; 
 int NAU8824_DAC_OVERSAMPLE_64 ; 
 int NAU8824_DAC_OVERSAMPLE_MASK ; 
 int NAU8824_DAC_ZC_EN ; 
 int NAU8824_DMIC_CLK_DRV_STRG ; 
 int NAU8824_DMIC_CLK_SLEW_FAST ; 
 int NAU8824_DRV_CURR_INC ; 
 int NAU8824_FEPGA_MODEL_SHORT_EN ; 
 int NAU8824_FEPGA_MODER_SHORT_EN ; 
 int NAU8824_GLOBAL_BIAS_EN ; 
 int NAU8824_HP_BOOST_DIS ; 
 int NAU8824_HP_BOOST_G_DIS ; 
 int NAU8824_JACK_EJECT_DT_MASK ; 
 int NAU8824_JACK_EJECT_DT_SFT ; 
 int NAU8824_JACK_LOGIC ; 
 int NAU8824_MICBIAS_VOLTAGE_MASK ; 
 int NAU8824_POWER_DOWN_DACL ; 
 int NAU8824_POWER_DOWN_DACR ; 
 int NAU8824_PRECHARGE_DIS ; 
 int NAU8824_RDAC_CLK_DELAY_MASK ; 
 int NAU8824_RDAC_CLK_DELAY_SFT ; 
 int NAU8824_RDAC_VREF_MASK ; 
 int NAU8824_RDAC_VREF_SFT ; 
 int /*<<< orphan*/  NAU8824_REG_ADC_FILTER_CTRL ; 
 int /*<<< orphan*/  NAU8824_REG_ANALOG_CONTROL_1 ; 
 int /*<<< orphan*/  NAU8824_REG_BIAS_ADJ ; 
 int /*<<< orphan*/  NAU8824_REG_BOOST ; 
 int /*<<< orphan*/  NAU8824_REG_CHARGE_PUMP_CONTROL ; 
 int /*<<< orphan*/  NAU8824_REG_CLASSG ; 
 int /*<<< orphan*/  NAU8824_REG_CLK_DIVIDER ; 
 int /*<<< orphan*/  NAU8824_REG_CLK_GATING_ENA ; 
 int /*<<< orphan*/  NAU8824_REG_DAC_CH0_DGAIN_CTRL ; 
 int /*<<< orphan*/  NAU8824_REG_DAC_CH1_DGAIN_CTRL ; 
 int /*<<< orphan*/  NAU8824_REG_DAC_FILTER_CTRL_1 ; 
 int /*<<< orphan*/  NAU8824_REG_DAC_MUTE_CTRL ; 
 int /*<<< orphan*/  NAU8824_REG_ENABLE_LO ; 
 int /*<<< orphan*/  NAU8824_REG_ENA_CTRL ; 
 int /*<<< orphan*/  NAU8824_REG_FEPGA ; 
 int /*<<< orphan*/  NAU8824_REG_JACK_DET_CTRL ; 
 int /*<<< orphan*/  NAU8824_REG_MIC_BIAS ; 
 int /*<<< orphan*/  NAU8824_REG_RDAC ; 
 int /*<<< orphan*/  NAU8824_REG_TRIM_SETTINGS ; 
 int NAU8824_SHORT_SHUTDOWN_EN ; 
 int NAU8824_SPKL_PULL_DOWN ; 
 int NAU8824_SPKR_PULL_DOWN ; 
 int NAU8824_TEST_DAC_EN ; 
 int NAU8824_VMID ; 
 int NAU8824_VMID_SEL_MASK ; 
 int NAU8824_VMID_SEL_SFT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  nau8824_setup_buttons (struct nau8824*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void nau8824_init_regs(struct nau8824 *nau8824)
{
	struct regmap *regmap = nau8824->regmap;

	/* Enable Bias/VMID/VMID Tieoff */
	regmap_update_bits(regmap, NAU8824_REG_BIAS_ADJ,
		NAU8824_VMID | NAU8824_VMID_SEL_MASK, NAU8824_VMID |
		(nau8824->vref_impedance << NAU8824_VMID_SEL_SFT));
	regmap_update_bits(regmap, NAU8824_REG_BOOST,
		NAU8824_GLOBAL_BIAS_EN, NAU8824_GLOBAL_BIAS_EN);
	mdelay(2);
	regmap_update_bits(regmap, NAU8824_REG_MIC_BIAS,
		NAU8824_MICBIAS_VOLTAGE_MASK, nau8824->micbias_voltage);
	/* Disable Boost Driver, Automatic Short circuit protection enable */
	regmap_update_bits(regmap, NAU8824_REG_BOOST,
		NAU8824_PRECHARGE_DIS | NAU8824_HP_BOOST_DIS |
		NAU8824_HP_BOOST_G_DIS | NAU8824_SHORT_SHUTDOWN_EN,
		NAU8824_PRECHARGE_DIS | NAU8824_HP_BOOST_DIS |
		NAU8824_HP_BOOST_G_DIS | NAU8824_SHORT_SHUTDOWN_EN);
	/* Scaling for ADC and DAC clock */
	regmap_update_bits(regmap, NAU8824_REG_CLK_DIVIDER,
		NAU8824_CLK_ADC_SRC_MASK | NAU8824_CLK_DAC_SRC_MASK,
		(0x1 << NAU8824_CLK_ADC_SRC_SFT) |
		(0x1 << NAU8824_CLK_DAC_SRC_SFT));
	regmap_update_bits(regmap, NAU8824_REG_DAC_MUTE_CTRL,
		NAU8824_DAC_ZC_EN, NAU8824_DAC_ZC_EN);
	regmap_update_bits(regmap, NAU8824_REG_ENA_CTRL,
		NAU8824_DAC_CH1_EN | NAU8824_DAC_CH0_EN |
		NAU8824_ADC_CH0_EN | NAU8824_ADC_CH1_EN |
		NAU8824_ADC_CH2_EN | NAU8824_ADC_CH3_EN,
		NAU8824_DAC_CH1_EN | NAU8824_DAC_CH0_EN |
		NAU8824_ADC_CH0_EN | NAU8824_ADC_CH1_EN |
		NAU8824_ADC_CH2_EN | NAU8824_ADC_CH3_EN);
	regmap_update_bits(regmap, NAU8824_REG_CLK_GATING_ENA,
		NAU8824_CLK_ADC_CH23_EN | NAU8824_CLK_ADC_CH01_EN |
		NAU8824_CLK_DAC_CH1_EN | NAU8824_CLK_DAC_CH0_EN |
		NAU8824_CLK_I2S_EN | NAU8824_CLK_GAIN_EN |
		NAU8824_CLK_SAR_EN | NAU8824_CLK_DMIC_CH23_EN,
		NAU8824_CLK_ADC_CH23_EN | NAU8824_CLK_ADC_CH01_EN |
		NAU8824_CLK_DAC_CH1_EN | NAU8824_CLK_DAC_CH0_EN |
		NAU8824_CLK_I2S_EN | NAU8824_CLK_GAIN_EN |
		NAU8824_CLK_SAR_EN | NAU8824_CLK_DMIC_CH23_EN);
	/* Class G timer 64ms */
	regmap_update_bits(regmap, NAU8824_REG_CLASSG,
		NAU8824_CLASSG_TIMER_MASK,
		0x20 << NAU8824_CLASSG_TIMER_SFT);
	regmap_update_bits(regmap, NAU8824_REG_TRIM_SETTINGS,
		NAU8824_DRV_CURR_INC, NAU8824_DRV_CURR_INC);
	/* Disable DACR/L power */
	regmap_update_bits(regmap, NAU8824_REG_CHARGE_PUMP_CONTROL,
		NAU8824_SPKR_PULL_DOWN | NAU8824_SPKL_PULL_DOWN |
		NAU8824_POWER_DOWN_DACR | NAU8824_POWER_DOWN_DACL,
		NAU8824_SPKR_PULL_DOWN | NAU8824_SPKL_PULL_DOWN |
		NAU8824_POWER_DOWN_DACR | NAU8824_POWER_DOWN_DACL);
	/* Enable TESTDAC. This sets the analog DAC inputs to a '0' input
	 * signal to avoid any glitches due to power up transients in both
	 * the analog and digital DAC circuit.
	 */
	regmap_update_bits(regmap, NAU8824_REG_ENABLE_LO,
		NAU8824_TEST_DAC_EN, NAU8824_TEST_DAC_EN);
	/* Config L/R channel */
	regmap_update_bits(regmap, NAU8824_REG_DAC_CH0_DGAIN_CTRL,
		NAU8824_DAC_CH0_SEL_MASK, NAU8824_DAC_CH0_SEL_I2S0);
	regmap_update_bits(regmap, NAU8824_REG_DAC_CH1_DGAIN_CTRL,
		NAU8824_DAC_CH1_SEL_MASK, NAU8824_DAC_CH1_SEL_I2S1);
	regmap_update_bits(regmap, NAU8824_REG_ENABLE_LO,
		NAU8824_DACR_HPR_EN | NAU8824_DACL_HPL_EN,
		NAU8824_DACR_HPR_EN | NAU8824_DACL_HPL_EN);
	/* Default oversampling/decimations settings are unusable
	 * (audible hiss). Set it to something better.
	 */
	regmap_update_bits(regmap, NAU8824_REG_ADC_FILTER_CTRL,
		NAU8824_ADC_SYNC_DOWN_MASK, NAU8824_ADC_SYNC_DOWN_64);
	regmap_update_bits(regmap, NAU8824_REG_DAC_FILTER_CTRL_1,
		NAU8824_DAC_CICCLP_OFF | NAU8824_DAC_OVERSAMPLE_MASK,
		NAU8824_DAC_CICCLP_OFF | NAU8824_DAC_OVERSAMPLE_64);
	/* DAC clock delay 2ns, VREF */
	regmap_update_bits(regmap, NAU8824_REG_RDAC,
		NAU8824_RDAC_CLK_DELAY_MASK | NAU8824_RDAC_VREF_MASK,
		(0x2 << NAU8824_RDAC_CLK_DELAY_SFT) |
		(0x3 << NAU8824_RDAC_VREF_SFT));
	/* PGA input mode selection */
	regmap_update_bits(regmap, NAU8824_REG_FEPGA,
		NAU8824_FEPGA_MODEL_SHORT_EN | NAU8824_FEPGA_MODER_SHORT_EN,
		NAU8824_FEPGA_MODEL_SHORT_EN | NAU8824_FEPGA_MODER_SHORT_EN);
	/* Digital microphone control */
	regmap_update_bits(regmap, NAU8824_REG_ANALOG_CONTROL_1,
		NAU8824_DMIC_CLK_DRV_STRG | NAU8824_DMIC_CLK_SLEW_FAST,
		NAU8824_DMIC_CLK_DRV_STRG | NAU8824_DMIC_CLK_SLEW_FAST);
	regmap_update_bits(regmap, NAU8824_REG_JACK_DET_CTRL,
		NAU8824_JACK_LOGIC,
		/* jkdet_polarity - 1  is for active-low */
		nau8824->jkdet_polarity ? 0 : NAU8824_JACK_LOGIC);
	regmap_update_bits(regmap,
		NAU8824_REG_JACK_DET_CTRL, NAU8824_JACK_EJECT_DT_MASK,
		(nau8824->jack_eject_debounce << NAU8824_JACK_EJECT_DT_SFT));
	if (nau8824->sar_threshold_num)
		nau8824_setup_buttons(nau8824);
}