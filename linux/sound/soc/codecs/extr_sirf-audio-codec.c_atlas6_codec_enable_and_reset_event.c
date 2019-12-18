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
struct sirf_audio_codec {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATLAS6_CODEC_ENABLE_BITS ; 
 int /*<<< orphan*/  ATLAS6_CODEC_RESET_BITS ; 
 int /*<<< orphan*/  AUDIO_IC_CODEC_CTRL1 ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  enable_and_reset_codec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sirf_audio_codec* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atlas6_codec_enable_and_reset_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
#define ATLAS6_CODEC_ENABLE_BITS (1 << 29)
#define ATLAS6_CODEC_RESET_BITS (1 << 28)
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct sirf_audio_codec *sirf_audio_codec = snd_soc_component_get_drvdata(component);
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		enable_and_reset_codec(sirf_audio_codec->regmap,
			ATLAS6_CODEC_ENABLE_BITS, ATLAS6_CODEC_RESET_BITS);
		break;
	case SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(sirf_audio_codec->regmap,
			AUDIO_IC_CODEC_CTRL1, ATLAS6_CODEC_ENABLE_BITS, 0);
		break;
	default:
		break;
	}

	return 0;
}