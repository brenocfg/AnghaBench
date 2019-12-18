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
struct snd_pcm_substream {int stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct mtk_base_afe {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_MEMIF_PBUF_SIZE ; 
 int /*<<< orphan*/  AFE_MEMIF_PBUF_SIZE_DLM_MASK ; 
 int /*<<< orphan*/  AFE_MEMIF_PBUF_SIZE_PAIR_INTERLEAVE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int mtk_afe_fe_hw_params (struct snd_pcm_substream*,struct snd_pcm_hw_params*,struct snd_soc_dai*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_base_afe* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mt2701_simple_fe_hw_params(struct snd_pcm_substream *substream,
				      struct snd_pcm_hw_params *params,
				      struct snd_soc_dai *dai)
{
	struct mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	int stream_dir = substream->stream;

	/* single DL use PAIR_INTERLEAVE */
	if (stream_dir == SNDRV_PCM_STREAM_PLAYBACK)
		regmap_update_bits(afe->regmap,
				   AFE_MEMIF_PBUF_SIZE,
				   AFE_MEMIF_PBUF_SIZE_DLM_MASK,
				   AFE_MEMIF_PBUF_SIZE_PAIR_INTERLEAVE);

	return mtk_afe_fe_hw_params(substream, params, dai);
}