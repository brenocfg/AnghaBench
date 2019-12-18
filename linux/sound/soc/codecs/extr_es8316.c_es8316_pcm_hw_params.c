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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct es8316_priv {unsigned int const sysclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ES8316_SERDATA2_LEN_16 ; 
 int /*<<< orphan*/  ES8316_SERDATA2_LEN_20 ; 
 int /*<<< orphan*/  ES8316_SERDATA2_LEN_24 ; 
 int /*<<< orphan*/  ES8316_SERDATA2_LEN_32 ; 
 int /*<<< orphan*/  ES8316_SERDATA2_LEN_MASK ; 
 int /*<<< orphan*/  ES8316_SERDATA_ADC ; 
 int /*<<< orphan*/  ES8316_SERDATA_DAC ; 
 int NR_SUPPORTED_MCLK_LRCK_RATIOS ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S20_3LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int params_format (struct snd_pcm_hw_params*) ; 
 unsigned int const params_rate (struct snd_pcm_hw_params*) ; 
 struct es8316_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int* supported_mclk_lrck_ratios ; 

__attribute__((used)) static int es8316_pcm_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct es8316_priv *es8316 = snd_soc_component_get_drvdata(component);
	u8 wordlen = 0;
	int i;

	/* Validate supported sample rates that are autodetected from MCLK */
	for (i = 0; i < NR_SUPPORTED_MCLK_LRCK_RATIOS; i++) {
		const unsigned int ratio = supported_mclk_lrck_ratios[i];

		if (es8316->sysclk % ratio != 0)
			continue;
		if (es8316->sysclk / ratio == params_rate(params))
			break;
	}
	if (i == NR_SUPPORTED_MCLK_LRCK_RATIOS)
		return -EINVAL;

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		wordlen = ES8316_SERDATA2_LEN_16;
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		wordlen = ES8316_SERDATA2_LEN_20;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		wordlen = ES8316_SERDATA2_LEN_24;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		wordlen = ES8316_SERDATA2_LEN_32;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, ES8316_SERDATA_DAC,
			    ES8316_SERDATA2_LEN_MASK, wordlen);
	snd_soc_component_update_bits(component, ES8316_SERDATA_ADC,
			    ES8316_SERDATA2_LEN_MASK, wordlen);
	return 0;
}