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
struct snd_soc_dapm_context {scalar_t__ bias_level; } ;
struct regmap {int dummy; } ;
struct nau8824 {struct regmap* regmap; struct snd_soc_dapm_context* dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU8824_CLK_DIS ; 
 int NAU8824_IRQ_EJECT_DIS ; 
 int NAU8824_IRQ_EJECT_EN ; 
 int NAU8824_IRQ_INSERT_DIS ; 
 int NAU8824_IRQ_INSERT_EN ; 
 int NAU8824_IRQ_KEY_RELEASE_DIS ; 
 int NAU8824_IRQ_KEY_SHORT_PRESS_DIS ; 
 int NAU8824_JD_SLEEP_MODE ; 
 int /*<<< orphan*/  NAU8824_REG_ENA_CTRL ; 
 int /*<<< orphan*/  NAU8824_REG_INTERRUPT_SETTING ; 
 int /*<<< orphan*/  NAU8824_REG_INTERRUPT_SETTING_1 ; 
 scalar_t__ SND_SOC_BIAS_PREPARE ; 
 int /*<<< orphan*/  nau8824_config_sysclk (struct nau8824*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nau8824_dapm_disable_pin (struct nau8824*,char*) ; 
 int /*<<< orphan*/  nau8824_int_status_clear_all (struct regmap*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static void nau8824_eject_jack(struct nau8824 *nau8824)
{
	struct snd_soc_dapm_context *dapm = nau8824->dapm;
	struct regmap *regmap = nau8824->regmap;

	/* Clear all interruption status */
	nau8824_int_status_clear_all(regmap);

	nau8824_dapm_disable_pin(nau8824, "SAR");
	nau8824_dapm_disable_pin(nau8824, "MICBIAS");
	snd_soc_dapm_sync(dapm);

	/* Enable the insertion interruption, disable the ejection
	 * interruption, and then bypass de-bounce circuit.
	 */
	regmap_update_bits(regmap, NAU8824_REG_INTERRUPT_SETTING,
		NAU8824_IRQ_KEY_RELEASE_DIS | NAU8824_IRQ_KEY_SHORT_PRESS_DIS |
		NAU8824_IRQ_EJECT_DIS | NAU8824_IRQ_INSERT_DIS,
		NAU8824_IRQ_KEY_RELEASE_DIS | NAU8824_IRQ_KEY_SHORT_PRESS_DIS |
		NAU8824_IRQ_EJECT_DIS);
	regmap_update_bits(regmap, NAU8824_REG_INTERRUPT_SETTING_1,
		NAU8824_IRQ_INSERT_EN | NAU8824_IRQ_EJECT_EN,
		NAU8824_IRQ_INSERT_EN);
	regmap_update_bits(regmap, NAU8824_REG_ENA_CTRL,
		NAU8824_JD_SLEEP_MODE, NAU8824_JD_SLEEP_MODE);

	/* Close clock for jack type detection at manual mode */
	if (dapm->bias_level < SND_SOC_BIAS_PREPARE)
		nau8824_config_sysclk(nau8824, NAU8824_CLK_DIS, 0);
}