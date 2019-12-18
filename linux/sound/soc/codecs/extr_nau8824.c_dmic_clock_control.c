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
struct nau8824 {int fs; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMIC_CLK ; 
 int /*<<< orphan*/  NAU8824_CLK_DMIC_SRC_MASK ; 
 int NAU8824_CLK_DMIC_SRC_SFT ; 
 int /*<<< orphan*/  NAU8824_REG_CLK_DIVIDER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nau8824* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmic_clock_control(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *k, int  event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	int src;

	/* The DMIC clock is gotten from system clock (256fs) divided by
	 * DMIC_SRC (1, 2, 4, 8, 16, 32). The clock has to be equal or
	 * less than 3.072 MHz.
	 */
	for (src = 0; src < 5; src++) {
		if ((0x1 << (8 - src)) * nau8824->fs <= DMIC_CLK)
			break;
	}
	dev_dbg(nau8824->dev, "dmic src %d for mclk %d\n", src, nau8824->fs * 256);
	regmap_update_bits(nau8824->regmap, NAU8824_REG_CLK_DIVIDER,
		NAU8824_CLK_DMIC_SRC_MASK, (src << NAU8824_CLK_DMIC_SRC_SFT));

	return 0;
}