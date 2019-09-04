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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int rate; int channels; } ;
struct mtk_base_afe {int /*<<< orphan*/  regmap; struct mt8173_afe_private* platform_priv; } ;
struct mt8173_afe_private {int /*<<< orphan*/ * clocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_HDMI_OUT_CON0 ; 
 unsigned int AFE_TDM_CH_START_O30_O31 ; 
 int AFE_TDM_CH_START_O32_O33 ; 
 int AFE_TDM_CH_START_O34_O35 ; 
 int AFE_TDM_CH_START_O36_O37 ; 
 int AFE_TDM_CH_ZERO ; 
 int /*<<< orphan*/  AFE_TDM_CON1 ; 
 unsigned int AFE_TDM_CON1_1_BCK_DELAY ; 
 unsigned int AFE_TDM_CON1_32_BCK_CYCLES ; 
 unsigned int AFE_TDM_CON1_BCK_INV ; 
 int AFE_TDM_CON1_EN ; 
 unsigned int AFE_TDM_CON1_LRCK_INV ; 
 unsigned int AFE_TDM_CON1_LRCK_WIDTH (int) ; 
 unsigned int AFE_TDM_CON1_MSB_ALIGNED ; 
 unsigned int AFE_TDM_CON1_WLEN_32BIT ; 
 int /*<<< orphan*/  AFE_TDM_CON2 ; 
 size_t MT8173_CLK_I2S3_B ; 
 size_t MT8173_CLK_I2S3_M ; 
 int /*<<< orphan*/  mt8173_afe_dais_set_clks (struct mtk_base_afe*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct mtk_base_afe* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mt8173_afe_hdmi_prepare(struct snd_pcm_substream *substream,
				   struct snd_soc_dai *dai)
{
	struct snd_pcm_runtime * const runtime = substream->runtime;
	struct mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	struct mt8173_afe_private *afe_priv = afe->platform_priv;

	unsigned int val;

	mt8173_afe_dais_set_clks(afe, afe_priv->clocks[MT8173_CLK_I2S3_M],
				 runtime->rate * 128,
				 afe_priv->clocks[MT8173_CLK_I2S3_B],
				 runtime->rate * runtime->channels * 32);

	val = AFE_TDM_CON1_BCK_INV |
	      AFE_TDM_CON1_LRCK_INV |
	      AFE_TDM_CON1_1_BCK_DELAY |
	      AFE_TDM_CON1_MSB_ALIGNED | /* I2S mode */
	      AFE_TDM_CON1_WLEN_32BIT |
	      AFE_TDM_CON1_32_BCK_CYCLES |
	      AFE_TDM_CON1_LRCK_WIDTH(32);
	regmap_update_bits(afe->regmap, AFE_TDM_CON1, ~AFE_TDM_CON1_EN, val);

	/* set tdm2 config */
	switch (runtime->channels) {
	case 1:
	case 2:
		val = AFE_TDM_CH_START_O30_O31;
		val |= (AFE_TDM_CH_ZERO << 4);
		val |= (AFE_TDM_CH_ZERO << 8);
		val |= (AFE_TDM_CH_ZERO << 12);
		break;
	case 3:
	case 4:
		val = AFE_TDM_CH_START_O30_O31;
		val |= (AFE_TDM_CH_START_O32_O33 << 4);
		val |= (AFE_TDM_CH_ZERO << 8);
		val |= (AFE_TDM_CH_ZERO << 12);
		break;
	case 5:
	case 6:
		val = AFE_TDM_CH_START_O30_O31;
		val |= (AFE_TDM_CH_START_O32_O33 << 4);
		val |= (AFE_TDM_CH_START_O34_O35 << 8);
		val |= (AFE_TDM_CH_ZERO << 12);
		break;
	case 7:
	case 8:
		val = AFE_TDM_CH_START_O30_O31;
		val |= (AFE_TDM_CH_START_O32_O33 << 4);
		val |= (AFE_TDM_CH_START_O34_O35 << 8);
		val |= (AFE_TDM_CH_START_O36_O37 << 12);
		break;
	default:
		val = 0;
	}
	regmap_update_bits(afe->regmap, AFE_TDM_CON2, 0x0000ffff, val);

	regmap_update_bits(afe->regmap, AFE_HDMI_OUT_CON0,
			   0x000000f0, runtime->channels << 4);
	return 0;
}