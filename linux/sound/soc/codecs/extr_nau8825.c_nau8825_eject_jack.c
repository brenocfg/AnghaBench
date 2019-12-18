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
struct snd_soc_dapm_context {int dummy; } ;
struct regmap {int dummy; } ;
struct nau8825 {struct regmap* regmap; struct snd_soc_dapm_context* dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU8825_CLK_DIS ; 
 int NAU8825_ENABLE_ADC ; 
 int NAU8825_IRQ_EJECT_DIS ; 
 int NAU8825_IRQ_EJECT_EN ; 
 int NAU8825_IRQ_HEADSET_COMPLETE_EN ; 
 int NAU8825_IRQ_INSERT_DIS ; 
 int NAU8825_IRQ_INSERT_EN ; 
 int NAU8825_IRQ_OUTPUT_EN ; 
 int NAU8825_JACK_DET_DB_BYPASS ; 
 int NAU8825_MICBIAS_JKR2 ; 
 int NAU8825_MICBIAS_JKSLV ; 
 int /*<<< orphan*/  NAU8825_REG_ENA_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_HSD_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_INTERRUPT_DIS_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_INTERRUPT_MASK ; 
 int /*<<< orphan*/  NAU8825_REG_JACK_DET_CTRL ; 
 int /*<<< orphan*/  NAU8825_REG_MIC_BIAS ; 
 int /*<<< orphan*/  nau8825_configure_sysclk (struct nau8825*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nau8825_int_status_clear_all (struct regmap*) ; 
 int /*<<< orphan*/  nau8825_xtalk_cancel (struct nau8825*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static void nau8825_eject_jack(struct nau8825 *nau8825)
{
	struct snd_soc_dapm_context *dapm = nau8825->dapm;
	struct regmap *regmap = nau8825->regmap;

	/* Force to cancel the cross talk detection process */
	nau8825_xtalk_cancel(nau8825);

	snd_soc_dapm_disable_pin(dapm, "SAR");
	snd_soc_dapm_disable_pin(dapm, "MICBIAS");
	/* Detach 2kOhm Resistors from MICBIAS to MICGND1/2 */
	regmap_update_bits(regmap, NAU8825_REG_MIC_BIAS,
		NAU8825_MICBIAS_JKSLV | NAU8825_MICBIAS_JKR2, 0);
	/* ground HPL/HPR, MICGRND1/2 */
	regmap_update_bits(regmap, NAU8825_REG_HSD_CTRL, 0xf, 0xf);

	snd_soc_dapm_sync(dapm);

	/* Clear all interruption status */
	nau8825_int_status_clear_all(regmap);

	/* Enable the insertion interruption, disable the ejection inter-
	 * ruption, and then bypass de-bounce circuit.
	 */
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_DIS_CTRL,
		NAU8825_IRQ_EJECT_DIS | NAU8825_IRQ_INSERT_DIS,
		NAU8825_IRQ_EJECT_DIS);
	regmap_update_bits(regmap, NAU8825_REG_INTERRUPT_MASK,
		NAU8825_IRQ_OUTPUT_EN | NAU8825_IRQ_EJECT_EN |
		NAU8825_IRQ_HEADSET_COMPLETE_EN | NAU8825_IRQ_INSERT_EN,
		NAU8825_IRQ_OUTPUT_EN | NAU8825_IRQ_EJECT_EN |
		NAU8825_IRQ_HEADSET_COMPLETE_EN);
	regmap_update_bits(regmap, NAU8825_REG_JACK_DET_CTRL,
		NAU8825_JACK_DET_DB_BYPASS, NAU8825_JACK_DET_DB_BYPASS);

	/* Disable ADC needed for interruptions at audo mode */
	regmap_update_bits(regmap, NAU8825_REG_ENA_CTRL,
		NAU8825_ENABLE_ADC, 0);

	/* Close clock for jack type detection at manual mode */
	nau8825_configure_sysclk(nau8825, NAU8825_CLK_DIS, 0);
}