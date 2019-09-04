#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_1__* cpu_dai; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct mtk_base_afe_memif {TYPE_2__* data; } ;
struct mtk_base_afe {struct mtk_base_afe_memif* memif; } ;
struct TYPE_4__ {scalar_t__ id; } ;
struct TYPE_3__ {size_t id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_PCM_NAME ; 
 int EINVAL ; 
 scalar_t__ MT8173_AFE_MEMIF_DAI ; 
 scalar_t__ MT8173_AFE_MEMIF_MOD_DAI ; 
 int mt8173_afe_i2s_fs (unsigned int) ; 
 struct mtk_base_afe* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt8173_memif_fs(struct snd_pcm_substream *substream,
			   unsigned int rate)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, AFE_PCM_NAME);
	struct mtk_base_afe *afe = snd_soc_component_get_drvdata(component);
	struct mtk_base_afe_memif *memif = &afe->memif[rtd->cpu_dai->id];
	int fs;

	if (memif->data->id == MT8173_AFE_MEMIF_DAI ||
	    memif->data->id == MT8173_AFE_MEMIF_MOD_DAI) {
		switch (rate) {
		case 8000:
			fs = 0;
			break;
		case 16000:
			fs = 1;
			break;
		case 32000:
			fs = 2;
			break;
		default:
			return -EINVAL;
		}
	} else {
		fs = mt8173_afe_i2s_fs(rate);
	}
	return fs;
}