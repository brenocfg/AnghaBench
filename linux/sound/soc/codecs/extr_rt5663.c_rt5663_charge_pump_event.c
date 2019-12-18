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
struct rt5663_priv {int /*<<< orphan*/  codec_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_VER_0 ; 
 int /*<<< orphan*/  RT5663_DEPOP_1 ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 struct rt5663_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5663_charge_pump_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct rt5663_priv *rt5663 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (rt5663->codec_ver == CODEC_VER_0) {
			snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x0030,
				0x0030);
			snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x0003,
				0x0003);
		}
		break;

	case SND_SOC_DAPM_POST_PMD:
		if (rt5663->codec_ver == CODEC_VER_0) {
			snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x0003, 0);
			snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x0030, 0);
		}
		break;

	default:
		return 0;
	}

	return 0;
}