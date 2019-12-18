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
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct rt5663_priv {scalar_t__ codec_ver; } ;

/* Variables and functions */
 scalar_t__ CODEC_VER_1 ; 
#define  RT5663_ADC_STO1_ASRC_SHIFT 129 
 unsigned int RT5663_AD_STO1_TRACK_SHIFT ; 
 unsigned int RT5663_ASRC_2 ; 
 unsigned int RT5663_ASRC_3 ; 
#define  RT5663_DAC_STO1_ASRC_SHIFT 128 
 unsigned int RT5663_DA_STO1_TRACK_SHIFT ; 
 unsigned int RT5663_V2_AD_STO1_TRACK_SHIFT ; 
 struct rt5663_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,unsigned int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5663_is_using_asrc(struct snd_soc_dapm_widget *w,
	struct snd_soc_dapm_widget *sink)
{
	unsigned int reg, shift, val;
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct rt5663_priv *rt5663 = snd_soc_component_get_drvdata(component);

	if (rt5663->codec_ver == CODEC_VER_1) {
		switch (w->shift) {
		case RT5663_ADC_STO1_ASRC_SHIFT:
			reg = RT5663_ASRC_3;
			shift = RT5663_V2_AD_STO1_TRACK_SHIFT;
			break;
		case RT5663_DAC_STO1_ASRC_SHIFT:
			reg = RT5663_ASRC_2;
			shift = RT5663_DA_STO1_TRACK_SHIFT;
			break;
		default:
			return 0;
		}
	} else {
		switch (w->shift) {
		case RT5663_ADC_STO1_ASRC_SHIFT:
			reg = RT5663_ASRC_2;
			shift = RT5663_AD_STO1_TRACK_SHIFT;
			break;
		case RT5663_DAC_STO1_ASRC_SHIFT:
			reg = RT5663_ASRC_2;
			shift = RT5663_DA_STO1_TRACK_SHIFT;
			break;
		default:
			return 0;
		}
	}

	val = (snd_soc_component_read32(component, reg) >> shift) & 0x7;

	if (val)
		return 1;

	return 0;
}