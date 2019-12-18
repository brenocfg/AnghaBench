#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct mtk_base_memif_data {int agent_disable_shift; int /*<<< orphan*/  agent_disable_reg; } ;
struct mtk_base_afe {int /*<<< orphan*/  regmap; TYPE_1__* memif; } ;
struct TYPE_2__ {struct mtk_base_memif_data* data; } ;

/* Variables and functions */
 int MT2701_MEMIF_DL1 ; 
 int MT2701_MEMIF_DL_SINGLE_NUM ; 
 void mtk_afe_fe_shutdown (struct snd_pcm_substream*,struct snd_soc_dai*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct mtk_base_afe* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void mt2701_dlm_fe_shutdown(struct snd_pcm_substream *substream,
				   struct snd_soc_dai *dai)
{
	struct mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	const struct mtk_base_memif_data *memif_data;
	int i;

	for (i = MT2701_MEMIF_DL1; i < MT2701_MEMIF_DL_SINGLE_NUM; ++i) {
		memif_data = afe->memif[i].data;
		regmap_update_bits(afe->regmap,
				   memif_data->agent_disable_reg,
				   1 << memif_data->agent_disable_shift,
				   1 << memif_data->agent_disable_shift);
	}

	return mtk_afe_fe_shutdown(substream, dai);
}