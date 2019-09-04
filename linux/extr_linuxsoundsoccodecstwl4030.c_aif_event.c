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
typedef  int u8 ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int TWL4030_AIF_EN ; 
 int /*<<< orphan*/  TWL4030_REG_AUDIO_IF ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_apll_enable (struct snd_soc_component*,int) ; 
 int twl4030_read (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aif_event(struct snd_soc_dapm_widget *w,
		     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u8 audio_if;

	audio_if = twl4030_read(component, TWL4030_REG_AUDIO_IF);
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* Enable AIF */
		/* enable the PLL before we use it to clock the DAI */
		twl4030_apll_enable(component, 1);

		twl4030_write(component, TWL4030_REG_AUDIO_IF,
			      audio_if | TWL4030_AIF_EN);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* disable the DAI before we stop it's source PLL */
		twl4030_write(component, TWL4030_REG_AUDIO_IF,
			      audio_if &  ~TWL4030_AIF_EN);
		twl4030_apll_enable(component, 0);
		break;
	}
	return 0;
}