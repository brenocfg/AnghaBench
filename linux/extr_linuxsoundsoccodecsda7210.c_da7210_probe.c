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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct da7210_priv {scalar_t__ master; scalar_t__ mclk_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7210_ADC ; 
 int DA7210_ADC_L_EN ; 
 int DA7210_ADC_R_EN ; 
 int /*<<< orphan*/  DA7210_AUX1_L ; 
 int DA7210_AUX1_L_EN ; 
 int /*<<< orphan*/  DA7210_AUX1_R ; 
 int DA7210_AUX1_R_EN ; 
 int /*<<< orphan*/  DA7210_AUX2 ; 
 int DA7210_AUX2_EN ; 
 int DA7210_BIAS_EN ; 
 int /*<<< orphan*/  DA7210_CONTROL ; 
 int DA7210_DAC_L_EN ; 
 int DA7210_DAC_L_SRC_DAI_L ; 
 int DA7210_DAC_R_EN ; 
 int DA7210_DAC_R_SRC_DAI_R ; 
 int /*<<< orphan*/  DA7210_DAC_SEL ; 
 int DA7210_HP_2CAP_MODE ; 
 int /*<<< orphan*/  DA7210_HP_CFG ; 
 int DA7210_HP_L_EN ; 
 int DA7210_HP_MODE ; 
 int DA7210_HP_R_EN ; 
 int DA7210_HP_SENSE_EN ; 
 int /*<<< orphan*/  DA7210_INMIX_L ; 
 int /*<<< orphan*/  DA7210_INMIX_R ; 
 int DA7210_IN_L_EN ; 
 int DA7210_IN_R_EN ; 
 int DA7210_MCLK_RANGE_10_20_MHZ ; 
 int DA7210_MICBIAS_EN ; 
 int /*<<< orphan*/  DA7210_MIC_L ; 
 int DA7210_MIC_L_EN ; 
 int /*<<< orphan*/  DA7210_MIC_R ; 
 int DA7210_MIC_R_EN ; 
 int /*<<< orphan*/  DA7210_OUT1_L ; 
 int DA7210_OUT1_L_EN ; 
 int /*<<< orphan*/  DA7210_OUT1_R ; 
 int DA7210_OUT1_R_EN ; 
 int /*<<< orphan*/  DA7210_OUT2 ; 
 int DA7210_OUT2_EN ; 
 int DA7210_OUT2_OUTMIX_L ; 
 int DA7210_OUT2_OUTMIX_R ; 
 int /*<<< orphan*/  DA7210_OUTMIX_L ; 
 int /*<<< orphan*/  DA7210_OUTMIX_R ; 
 int DA7210_OUT_L_EN ; 
 int DA7210_OUT_R_EN ; 
 int /*<<< orphan*/  DA7210_PLL ; 
 int DA7210_PLL_BYP ; 
 int /*<<< orphan*/  DA7210_PLL_DIV3 ; 
 int DA7210_PLL_FS_48000 ; 
 int DA7210_RAMP_EN ; 
 int DA7210_REG_EN ; 
 int DA7210_SC_MST_EN ; 
 int /*<<< orphan*/  DA7210_SOFTMUTE ; 
 int /*<<< orphan*/  DA7210_STARTUP1 ; 
 int /*<<< orphan*/  DA7210_VERSION ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct da7210_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int da7210_probe(struct snd_soc_component *component)
{
	struct da7210_priv *da7210 = snd_soc_component_get_drvdata(component);

	dev_info(component->dev, "DA7210 Audio Codec %s\n", DA7210_VERSION);

	da7210->mclk_rate       = 0;    /* This will be set from set_sysclk() */
	da7210->master          = 0;    /* This will be set from set_fmt() */

	/* Enable internal regulator & bias current */
	snd_soc_component_write(component, DA7210_CONTROL, DA7210_REG_EN | DA7210_BIAS_EN);

	/*
	 * ADC settings
	 */

	/* Enable Left & Right MIC PGA and Mic Bias */
	snd_soc_component_write(component, DA7210_MIC_L, DA7210_MIC_L_EN | DA7210_MICBIAS_EN);
	snd_soc_component_write(component, DA7210_MIC_R, DA7210_MIC_R_EN);

	/* Enable Left and Right input PGA */
	snd_soc_component_write(component, DA7210_INMIX_L, DA7210_IN_L_EN);
	snd_soc_component_write(component, DA7210_INMIX_R, DA7210_IN_R_EN);

	/* Enable Left and Right ADC */
	snd_soc_component_write(component, DA7210_ADC, DA7210_ADC_L_EN | DA7210_ADC_R_EN);

	/*
	 * DAC settings
	 */

	/* Enable Left and Right DAC */
	snd_soc_component_write(component, DA7210_DAC_SEL,
		     DA7210_DAC_L_SRC_DAI_L | DA7210_DAC_L_EN |
		     DA7210_DAC_R_SRC_DAI_R | DA7210_DAC_R_EN);

	/* Enable Left and Right out PGA */
	snd_soc_component_write(component, DA7210_OUTMIX_L, DA7210_OUT_L_EN);
	snd_soc_component_write(component, DA7210_OUTMIX_R, DA7210_OUT_R_EN);

	/* Enable Left and Right HeadPhone PGA */
	snd_soc_component_write(component, DA7210_HP_CFG,
		     DA7210_HP_2CAP_MODE | DA7210_HP_SENSE_EN |
		     DA7210_HP_L_EN | DA7210_HP_MODE | DA7210_HP_R_EN);

	/* Enable ramp mode for DAC gain update */
	snd_soc_component_write(component, DA7210_SOFTMUTE, DA7210_RAMP_EN);

	/*
	 * For DA7210 codec, there are two ways to enable/disable analog IOs
	 * and ADC/DAC,
	 * (1) Using "Enable Bit" of register associated with that IO
	 * (or ADC/DAC)
	 *	e.g. Mic Left can be enabled using bit 7 of MIC_L(0x7) reg
	 *
	 * (2) Using "Standby Bit" of STARTUP2 or STARTUP3 register
	 *	e.g. Mic left can be put to STANDBY using bit 0 of STARTUP3(0x5)
	 *
	 * Out of these two methods, the one using STANDBY bits is preferred
	 * way to enable/disable individual blocks. This is because STANDBY
	 * registers are part of system controller which allows system power
	 * up/down in a controlled, pop-free manner. Also, as per application
	 * note of DA7210, STANDBY register bits are only effective if a
	 * particular IO (or ADC/DAC) is already enabled using enable/disable
	 * register bits. Keeping these things in mind, current DAPM
	 * implementation manipulates only STANDBY bits.
	 *
	 * Overall implementation can be outlined as below,
	 *
	 * - "Enable bit" of an IO or ADC/DAC is used to enable it in probe()
	 * - "STANDBY bit" is controlled by DAPM
	 */

	/* Enable Line out amplifiers */
	snd_soc_component_write(component, DA7210_OUT1_L, DA7210_OUT1_L_EN);
	snd_soc_component_write(component, DA7210_OUT1_R, DA7210_OUT1_R_EN);
	snd_soc_component_write(component, DA7210_OUT2, DA7210_OUT2_EN |
		     DA7210_OUT2_OUTMIX_L | DA7210_OUT2_OUTMIX_R);

	/* Enable Aux1 */
	snd_soc_component_write(component, DA7210_AUX1_L, DA7210_AUX1_L_EN);
	snd_soc_component_write(component, DA7210_AUX1_R, DA7210_AUX1_R_EN);
	/* Enable Aux2 */
	snd_soc_component_write(component, DA7210_AUX2, DA7210_AUX2_EN);

	/* Set PLL Master clock range 10-20 MHz, enable PLL bypass */
	snd_soc_component_write(component, DA7210_PLL_DIV3, DA7210_MCLK_RANGE_10_20_MHZ |
					      DA7210_PLL_BYP);

	/* Diable PLL and bypass it */
	snd_soc_component_write(component, DA7210_PLL, DA7210_PLL_FS_48000);

	/* Activate all enabled subsystem */
	snd_soc_component_write(component, DA7210_STARTUP1, DA7210_SC_MST_EN);

	dev_info(component->dev, "DA7210 Audio Codec %s\n", DA7210_VERSION);

	return 0;
}