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
struct nau8825 {int vref_impedance; int jack_insert_debounce; int jack_eject_debounce; int micbias_voltage; struct regmap* regmap; scalar_t__ sar_threshold_num; scalar_t__ jkdet_polarity; scalar_t__ jkdet_pull_up; scalar_t__ jkdet_pull_enable; scalar_t__ jkdet_enable; } ;

/* Variables and functions */
 int NAU8825_ADC_SINC4_EN ; 
 int NAU8825_ADC_SYNC_DOWN_64 ; 
 int NAU8825_ADC_SYNC_DOWN_MASK ; 
 int NAU8825_BIAS_TESTDAC_EN ; 
 int NAU8825_BIAS_VMID ; 
 int NAU8825_BIAS_VMID_SEL_MASK ; 
 int NAU8825_BIAS_VMID_SEL_SFT ; 
 int NAU8825_CLASSG_TIMER_MASK ; 
 int NAU8825_CLASSG_TIMER_SFT ; 
 int NAU8825_DACL_CH_SEL_L ; 
 int NAU8825_DACL_CH_SEL_MASK ; 
 int NAU8825_DACL_CH_SEL_R ; 
 int NAU8825_DAC_CAPACITOR_LSB ; 
 int NAU8825_DAC_CAPACITOR_MSB ; 
 int NAU8825_DAC_CLIP_OFF ; 
 int NAU8825_DAC_OVERSAMPLE_64 ; 
 int NAU8825_DAC_OVERSAMPLE_MASK ; 
 int NAU8825_DIS_FS_SHORT_DET ; 
 int NAU8825_GLOBAL_BIAS_EN ; 
 int NAU8825_HP_BOOST_DIS ; 
 int NAU8825_HP_BOOST_G_DIS ; 
 int NAU8825_HP_NON_CLASSG_CURRENT_2xADJ ; 
 int NAU8825_IRQ_PIN_PULLUP ; 
 int NAU8825_IRQ_PIN_PULL_EN ; 
 int NAU8825_JACK_EJECT_DEBOUNCE_MASK ; 
 int NAU8825_JACK_EJECT_DEBOUNCE_SFT ; 
 int NAU8825_JACK_INSERT_DEBOUNCE_MASK ; 
 int NAU8825_JACK_INSERT_DEBOUNCE_SFT ; 
 int NAU8825_JACK_POLARITY ; 
 int NAU8825_JKDET_OUTPUT_EN ; 
 int NAU8825_JKDET_PULL_EN ; 
 int NAU8825_JKDET_PULL_UP ; 
 int NAU8825_MICBIAS_VOLTAGE_MASK ; 
 int NAU8825_POWER_DOWN_DACL ; 
 int NAU8825_POWER_DOWN_DACR ; 
 int NAU8825_PRECHARGE_DIS ; 
 int NAU8825_RDAC_CLK_DELAY_MASK ; 
 int NAU8825_RDAC_CLK_DELAY_SFT ; 
 int NAU8825_RDAC_VREF_MASK ; 
 int NAU8825_RDAC_VREF_SFT ; 
 int /*<<< orphan*/  NAU8825_REG_ADC_RATE ; 
 int /*<<< orphan*/  NAU8825_REG_ANALOG_CONTROL_2 ; 
 int /*<<< orphan*/  NAU8825_REG_BIAS_ADJ ; 
 int /*<<< orphan*/  NAU8825_REG_BOOST ; 
 int /*<<< orphan*/  NAU8825_REG_CHARGE_PUMP ; 
 int /*<<< orphan*/  NAU8825_REG_CLASSG_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_DACL_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_DACR_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_DAC_CTRL1 ; 
 int /*<<< orphan*/  NAU8825_REG_GPIO12_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_IIC_ADDR_SET ; 
 int /*<<< orphan*/  NAU8825_REG_INTERRUPT_MASK ; 
 int /*<<< orphan*/  NAU8825_REG_JACK_DET_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_LEFT_TIME_SLOT ; 
 int /*<<< orphan*/  NAU8825_REG_MIC_BIAS ; 
 int /*<<< orphan*/  NAU8825_REG_RDAC ; 
 int NAU8825_SHORT_SHUTDOWN_EN ; 
 int /*<<< orphan*/  nau8825_setup_buttons (struct nau8825*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nau8825_init_regs(struct nau8825 *nau8825)
{
	struct regmap *regmap = nau8825->regmap;

	/* Latch IIC LSB value */
	regmap_write(regmap, NAU8825_REG_IIC_ADDR_SET, 0x0001);
	/* Enable Bias/Vmid */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
		NAU8825_BIAS_VMID, NAU8825_BIAS_VMID);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BOOST,
		NAU8825_GLOBAL_BIAS_EN, NAU8825_GLOBAL_BIAS_EN);

	/* VMID Tieoff */
	regmap_update_bits(regmap, NAU8825_REG_BIAS_ADJ,
		NAU8825_BIAS_VMID_SEL_MASK,
		nau8825->vref_impedance << NAU8825_BIAS_VMID_SEL_SFT);
	/* Disable Boost Driver, Automatic Short circuit protection enable */
	regmap_update_bits(regmap, NAU8825_REG_BOOST,
		NAU8825_PRECHARGE_DIS | NAU8825_HP_BOOST_DIS |
		NAU8825_HP_BOOST_G_DIS | NAU8825_SHORT_SHUTDOWN_EN,
		NAU8825_PRECHARGE_DIS | NAU8825_HP_BOOST_DIS |
		NAU8825_HP_BOOST_G_DIS | NAU8825_SHORT_SHUTDOWN_EN);

	regmap_update_bits(regmap, NAU8825_REG_GPIO12_CTRL,
		NAU8825_JKDET_OUTPUT_EN,
		nau8825->jkdet_enable ? 0 : NAU8825_JKDET_OUTPUT_EN);
	regmap_update_bits(regmap, NAU8825_REG_GPIO12_CTRL,
		NAU8825_JKDET_PULL_EN,
		nau8825->jkdet_pull_enable ? 0 : NAU8825_JKDET_PULL_EN);
	regmap_update_bits(regmap, NAU8825_REG_GPIO12_CTRL,
		NAU8825_JKDET_PULL_UP,
		nau8825->jkdet_pull_up ? NAU8825_JKDET_PULL_UP : 0);
	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_POLARITY,
		/* jkdet_polarity - 1  is for active-low */
		nau8825->jkdet_polarity ? 0 : NAU8825_JACK_POLARITY);

	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_INSERT_DEBOUNCE_MASK,
		nau8825->jack_insert_debounce << NAU8825_JACK_INSERT_DEBOUNCE_SFT);
	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_EJECT_DEBOUNCE_MASK,
		nau8825->jack_eject_debounce << NAU8825_JACK_EJECT_DEBOUNCE_SFT);

	/* Pull up IRQ pin */
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_MASK,
		NAU8825_IRQ_PIN_PULLUP | NAU8825_IRQ_PIN_PULL_EN,
		NAU8825_IRQ_PIN_PULLUP | NAU8825_IRQ_PIN_PULL_EN);
	/* Mask unneeded IRQs: 1 - disable, 0 - enable */
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_MASK, 0x7ff, 0x7ff);

	regmap_update_bits(regmap, NAU8825_REG_MIC_BIAS,
		NAU8825_MICBIAS_VOLTAGE_MASK, nau8825->micbias_voltage);

	if (nau8825->sar_threshold_num)
		nau8825_setup_buttons(nau8825);

	/* Default oversampling/decimations settings are unusable
	 * (audible hiss). Set it to something better.
	 */
	regmap_update_bits(regmap, NAU8825_REG_ADC_RATE,
		NAU8825_ADC_SYNC_DOWN_MASK | NAU8825_ADC_SINC4_EN,
		NAU8825_ADC_SYNC_DOWN_64);
	regmap_update_bits(regmap, NAU8825_REG_DAC_CTRL1,
		NAU8825_DAC_OVERSAMPLE_MASK, NAU8825_DAC_OVERSAMPLE_64);
	/* Disable DACR/L power */
	regmap_update_bits(regmap, NAU8825_REG_CHARGE_PUMP,
		NAU8825_POWER_DOWN_DACR | NAU8825_POWER_DOWN_DACL,
		NAU8825_POWER_DOWN_DACR | NAU8825_POWER_DOWN_DACL);
	/* Enable TESTDAC. This sets the analog DAC inputs to a '0' input
	 * signal to avoid any glitches due to power up transients in both
	 * the analog and digital DAC circuit.
	 */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_BIAS_ADJ,
		NAU8825_BIAS_TESTDAC_EN, NAU8825_BIAS_TESTDAC_EN);
	/* CICCLP off */
	regmap_update_bits(regmap, NAU8825_REG_DAC_CTRL1,
		NAU8825_DAC_CLIP_OFF, NAU8825_DAC_CLIP_OFF);

	/* Class AB bias current to 2x, DAC Capacitor enable MSB/LSB */
	regmap_update_bits(regmap, NAU8825_REG_ANALOG_CONTROL_2,
		NAU8825_HP_NON_CLASSG_CURRENT_2xADJ |
		NAU8825_DAC_CAPACITOR_MSB | NAU8825_DAC_CAPACITOR_LSB,
		NAU8825_HP_NON_CLASSG_CURRENT_2xADJ |
		NAU8825_DAC_CAPACITOR_MSB | NAU8825_DAC_CAPACITOR_LSB);
	/* Class G timer 64ms */
	regmap_update_bits(regmap, NAU8825_REG_CLASSG_CTRL,
		NAU8825_CLASSG_TIMER_MASK,
		0x20 << NAU8825_CLASSG_TIMER_SFT);
	/* DAC clock delay 2ns, VREF */
	regmap_update_bits(regmap, NAU8825_REG_RDAC,
		NAU8825_RDAC_CLK_DELAY_MASK | NAU8825_RDAC_VREF_MASK,
		(0x2 << NAU8825_RDAC_CLK_DELAY_SFT) |
		(0x3 << NAU8825_RDAC_VREF_SFT));
	/* Config L/R channel */
	regmap_update_bits(nau8825->regmap, NAU8825_REG_DACL_CTRL,
		NAU8825_DACL_CH_SEL_MASK, NAU8825_DACL_CH_SEL_L);
	regmap_update_bits(nau8825->regmap, NAU8825_REG_DACR_CTRL,
		NAU8825_DACL_CH_SEL_MASK, NAU8825_DACL_CH_SEL_R);
	/* Disable short Frame Sync detection logic */
	regmap_update_bits(regmap, NAU8825_REG_LEFT_TIME_SLOT,
		NAU8825_DIS_FS_SHORT_DET, NAU8825_DIS_FS_SHORT_DET);
}