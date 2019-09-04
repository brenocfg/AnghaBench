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
struct snd_soc_dapm_widget {char* name; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct adau1373 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1373_PLL_CTRL6 (unsigned int) ; 
 unsigned int ADAU1373_PLL_CTRL6_PLL_EN ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct adau1373* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1373_pll_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	unsigned int pll_id = w->name[3] - '1';
	unsigned int val;

	if (SND_SOC_DAPM_EVENT_ON(event))
		val = ADAU1373_PLL_CTRL6_PLL_EN;
	else
		val = 0;

	regmap_update_bits(adau1373->regmap, ADAU1373_PLL_CTRL6(pll_id),
		ADAU1373_PLL_CTRL6_PLL_EN, val);

	if (SND_SOC_DAPM_EVENT_ON(event))
		mdelay(5);

	return 0;
}