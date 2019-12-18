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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct mtk_base_afe_memif {int irq_usage; int /*<<< orphan*/ * substream; int /*<<< orphan*/  const_irq; TYPE_2__* data; } ;
struct mtk_base_afe {int /*<<< orphan*/  regmap; struct mtk_base_afe_memif* memif; } ;
struct TYPE_4__ {int /*<<< orphan*/  agent_disable_shift; int /*<<< orphan*/  agent_disable_reg; } ;
struct TYPE_3__ {size_t id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_dynamic_irq_release (struct mtk_base_afe*,int) ; 
 int /*<<< orphan*/  mtk_regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct mtk_base_afe* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

void mtk_afe_fe_shutdown(struct snd_pcm_substream *substream,
			 struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	struct mtk_base_afe_memif *memif = &afe->memif[rtd->cpu_dai->id];
	int irq_id;

	irq_id = memif->irq_usage;

	mtk_regmap_update_bits(afe->regmap, memif->data->agent_disable_reg,
			       1, 1, memif->data->agent_disable_shift);

	if (!memif->const_irq) {
		mtk_dynamic_irq_release(afe, irq_id);
		memif->irq_usage = -1;
		memif->substream = NULL;
	}
}