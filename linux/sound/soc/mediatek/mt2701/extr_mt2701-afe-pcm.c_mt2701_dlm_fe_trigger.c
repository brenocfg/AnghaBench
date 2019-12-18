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
struct mtk_base_afe_memif {TYPE_1__* data; } ;
struct mtk_base_afe {int /*<<< orphan*/  regmap; struct mtk_base_afe_memif* memif; } ;
struct TYPE_2__ {int enable_shift; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MT2701_MEMIF_DL1 ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  mtk_afe_fe_trigger (struct snd_pcm_substream*,int,struct snd_soc_dai*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct mtk_base_afe* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mt2701_dlm_fe_trigger(struct snd_pcm_substream *substream,
				 int cmd, struct snd_soc_dai *dai)
{
	struct mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	struct mtk_base_afe_memif *memif_tmp = &afe->memif[MT2701_MEMIF_DL1];

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		regmap_update_bits(afe->regmap, memif_tmp->data->enable_reg,
				   1 << memif_tmp->data->enable_shift,
				   1 << memif_tmp->data->enable_shift);
		mtk_afe_fe_trigger(substream, cmd, dai);
		return 0;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		mtk_afe_fe_trigger(substream, cmd, dai);
		regmap_update_bits(afe->regmap, memif_tmp->data->enable_reg,
				   1 << memif_tmp->data->enable_shift, 0);

		return 0;
	default:
		return -EINVAL;
	}
}