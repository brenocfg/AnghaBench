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
struct adau {int* pll_regs; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU17X1_CLOCK_CONTROL ; 
 int /*<<< orphan*/  ADAU17X1_CLOCK_CONTROL_CORECLK_SRC_PLL ; 
 int /*<<< orphan*/  ADAU17X1_PLL_CONTROL ; 
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regmap_raw_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau17x1_pll_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct adau *adau = snd_soc_component_get_drvdata(component);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		adau->pll_regs[5] = 1;
	} else {
		adau->pll_regs[5] = 0;
		/* Bypass the PLL when disabled, otherwise registers will become
		 * inaccessible. */
		regmap_update_bits(adau->regmap, ADAU17X1_CLOCK_CONTROL,
			ADAU17X1_CLOCK_CONTROL_CORECLK_SRC_PLL, 0);
	}

	/* The PLL register is 6 bytes long and can only be written at once. */
	regmap_raw_write(adau->regmap, ADAU17X1_PLL_CONTROL,
			adau->pll_regs, ARRAY_SIZE(adau->pll_regs));

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		mdelay(5);
		regmap_update_bits(adau->regmap, ADAU17X1_CLOCK_CONTROL,
			ADAU17X1_CLOCK_CONTROL_CORECLK_SRC_PLL,
			ADAU17X1_CLOCK_CONTROL_CORECLK_SRC_PLL);
	}

	return 0;
}