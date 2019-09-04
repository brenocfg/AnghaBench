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
struct nau8825 {int /*<<< orphan*/  mclk; int /*<<< orphan*/  mclk_freq; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int NAU8825_ENABLE_ADC ; 
 int NAU8825_MICBIAS_JKR2 ; 
 int NAU8825_MICBIAS_JKSLV ; 
 int /*<<< orphan*/  NAU8825_REG_ENA_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_HSD_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_INTERRUPT_DIS_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_MIC_BIAS ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nau8825_resume_setup (struct nau8825*) ; 
 int /*<<< orphan*/  nau8825_xtalk_cancel (struct nau8825*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct nau8825* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int nau8825_set_bias_level(struct snd_soc_component *component,
				   enum snd_soc_bias_level level)
{
	struct nau8825 *nau8825 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			if (nau8825->mclk_freq) {
				ret = clk_prepare_enable(nau8825->mclk);
				if (ret) {
					dev_err(nau8825->dev, "Unable to prepare component mclk\n");
					return ret;
				}
			}
			/* Setup codec configuration after resume */
			nau8825_resume_setup(nau8825);
		}
		break;

	case SND_SOC_BIAS_OFF:
		/* Reset the configuration of jack type for detection */
		/* Detach 2kOhm Resistors from MICBIAS to MICGND1/2 */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_MIC_BIAS,
			NAU8825_MICBIAS_JKSLV | NAU8825_MICBIAS_JKR2, 0);
		/* ground HPL/HPR, MICGRND1/2 */
		regmap_update_bits(nau8825->regmap,
			NAU8825_REG_HSD_CTRL, 0xf, 0xf);
		/* Cancel and reset cross talk detection funciton */
		nau8825_xtalk_cancel(nau8825);
		/* Turn off all interruptions before system shutdown. Keep the
		 * interruption quiet before resume setup completes.
		 */
		regmap_write(nau8825->regmap,
			NAU8825_REG_INTERRUPT_DIS_CTRL, 0xffff);
		/* Disable ADC needed for interruptions at audo mode */
		regmap_update_bits(nau8825->regmap, NAU8825_REG_ENA_CTRL,
			NAU8825_ENABLE_ADC, 0);
		if (nau8825->mclk_freq)
			clk_disable_unprepare(nau8825->mclk);
		break;
	}
	return 0;
}