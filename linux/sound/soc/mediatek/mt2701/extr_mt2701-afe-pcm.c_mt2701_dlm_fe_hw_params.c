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
struct snd_pcm_hw_params {int dummy; } ;
struct mtk_base_afe {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_MEMIF_PBUF_SIZE ; 
 int /*<<< orphan*/  AFE_MEMIF_PBUF_SIZE_DLM_32BYTES ; 
 int /*<<< orphan*/  AFE_MEMIF_PBUF_SIZE_DLM_BYTE_MASK ; 
 int /*<<< orphan*/  AFE_MEMIF_PBUF_SIZE_DLM_CH (int) ; 
 int /*<<< orphan*/  AFE_MEMIF_PBUF_SIZE_DLM_CH_MASK ; 
 int /*<<< orphan*/  AFE_MEMIF_PBUF_SIZE_DLM_MASK ; 
 int /*<<< orphan*/  AFE_MEMIF_PBUF_SIZE_FULL_INTERLEAVE ; 
 int mtk_afe_fe_hw_params (struct snd_pcm_substream*,struct snd_pcm_hw_params*,struct snd_soc_dai*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_base_afe* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mt2701_dlm_fe_hw_params(struct snd_pcm_substream *substream,
				   struct snd_pcm_hw_params *params,
				   struct snd_soc_dai *dai)
{
	struct mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	int channels = params_channels(params);

	regmap_update_bits(afe->regmap,
			   AFE_MEMIF_PBUF_SIZE,
			   AFE_MEMIF_PBUF_SIZE_DLM_MASK,
			   AFE_MEMIF_PBUF_SIZE_FULL_INTERLEAVE);
	regmap_update_bits(afe->regmap,
			   AFE_MEMIF_PBUF_SIZE,
			   AFE_MEMIF_PBUF_SIZE_DLM_BYTE_MASK,
			   AFE_MEMIF_PBUF_SIZE_DLM_32BYTES);
	regmap_update_bits(afe->regmap,
			   AFE_MEMIF_PBUF_SIZE,
			   AFE_MEMIF_PBUF_SIZE_DLM_CH_MASK,
			   AFE_MEMIF_PBUF_SIZE_DLM_CH(channels));

	return mtk_afe_fe_hw_params(substream, params, dai);
}