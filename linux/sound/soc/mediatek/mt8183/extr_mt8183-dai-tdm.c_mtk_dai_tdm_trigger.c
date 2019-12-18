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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct mtk_base_afe {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_HDMI_OUT_CON0 ; 
 int /*<<< orphan*/  AFE_HDMI_OUT_ON_MASK_SFT ; 
 int AFE_HDMI_OUT_ON_SFT ; 
 int /*<<< orphan*/  AFE_TDM_CON1 ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  TDM_EN_MASK_SFT ; 
 int TDM_EN_SFT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mtk_base_afe* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mtk_dai_tdm_trigger(struct snd_pcm_substream *substream,
			       int cmd,
			       struct snd_soc_dai *dai)
{
	struct mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		/* enable Out control */
		regmap_update_bits(afe->regmap, AFE_HDMI_OUT_CON0,
				   AFE_HDMI_OUT_ON_MASK_SFT,
				   0x1 << AFE_HDMI_OUT_ON_SFT);
		/* enable tdm */
		regmap_update_bits(afe->regmap, AFE_TDM_CON1,
				   TDM_EN_MASK_SFT, 0x1 << TDM_EN_SFT);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		/* disable tdm */
		regmap_update_bits(afe->regmap, AFE_TDM_CON1,
				   TDM_EN_MASK_SFT, 0);
		/* disable Out control */
		regmap_update_bits(afe->regmap, AFE_HDMI_OUT_CON0,
				   AFE_HDMI_OUT_ON_MASK_SFT,
				   0);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}