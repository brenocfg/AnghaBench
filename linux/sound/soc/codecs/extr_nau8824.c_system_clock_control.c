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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct regmap {int dummy; } ;
struct nau8824 {int /*<<< orphan*/  dev; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU8824_CLK_DIS ; 
 int /*<<< orphan*/  NAU8824_CLK_INTERNAL ; 
 int /*<<< orphan*/  NAU8824_CLK_MCLK ; 
 unsigned int NAU8824_CLK_SRC_MASK ; 
 unsigned int NAU8824_CLK_SRC_VCO ; 
 unsigned int NAU8824_DCO_EN ; 
 unsigned int NAU8824_FLL_RATIO_MASK ; 
 int /*<<< orphan*/  NAU8824_REG_CLK_DIVIDER ; 
 int /*<<< orphan*/  NAU8824_REG_FLL1 ; 
 int /*<<< orphan*/  NAU8824_REG_FLL6 ; 
 scalar_t__ SND_SOC_DAPM_EVENT_OFF (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nau8824_config_sysclk (struct nau8824*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nau8824_is_jack_inserted (struct nau8824*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct nau8824* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int system_clock_control(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *k, int  event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	struct regmap *regmap = nau8824->regmap;
	unsigned int value;
	bool clk_fll, error;

	if (SND_SOC_DAPM_EVENT_OFF(event)) {
		dev_dbg(nau8824->dev, "system clock control : POWER OFF\n");
		/* Set clock source to disable or internal clock before the
		 * playback or capture end. Codec needs clock for Jack
		 * detection and button press if jack inserted; otherwise,
		 * the clock should be closed.
		 */
		if (nau8824_is_jack_inserted(nau8824)) {
			nau8824_config_sysclk(nau8824,
				NAU8824_CLK_INTERNAL, 0);
		} else {
			nau8824_config_sysclk(nau8824, NAU8824_CLK_DIS, 0);
		}
	} else {
		dev_dbg(nau8824->dev, "system clock control : POWER ON\n");
		/* Check the clock source setting is proper or not
		 * no matter the source is from FLL or MCLK.
		 */
		regmap_read(regmap, NAU8824_REG_FLL1, &value);
		clk_fll = value & NAU8824_FLL_RATIO_MASK;
		/* It's error to use internal clock when playback */
		regmap_read(regmap, NAU8824_REG_FLL6, &value);
		error = value & NAU8824_DCO_EN;
		if (!error) {
			/* Check error depending on source is FLL or MCLK. */
			regmap_read(regmap, NAU8824_REG_CLK_DIVIDER, &value);
			if (clk_fll)
				error = !(value & NAU8824_CLK_SRC_VCO);
			else
				error = value & NAU8824_CLK_SRC_VCO;
		}
		/* Recover the clock source setting if error. */
		if (error) {
			if (clk_fll) {
				regmap_update_bits(regmap,
					NAU8824_REG_FLL6, NAU8824_DCO_EN, 0);
				regmap_update_bits(regmap,
					NAU8824_REG_CLK_DIVIDER,
					NAU8824_CLK_SRC_MASK,
					NAU8824_CLK_SRC_VCO);
			} else {
				nau8824_config_sysclk(nau8824,
					NAU8824_CLK_MCLK, 0);
			}
		}
	}

	return 0;
}