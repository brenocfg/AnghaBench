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
typedef  int u32 ;
struct mtk_base_afe_memif {size_t irq_usage; int /*<<< orphan*/  substream; } ;
struct mtk_base_afe_irq {TYPE_1__* irq_data; } ;
struct mtk_base_afe {struct mtk_base_afe_irq* irqs; struct mtk_base_afe_memif* memif; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int irq_clr_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYS_IRQ_CLR ; 
 int /*<<< orphan*/  ASYS_IRQ_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MT2701_MEMIF_NUM ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mt2701_asys_isr(int irq_id, void *dev)
{
	int id;
	struct mtk_base_afe *afe = dev;
	struct mtk_base_afe_memif *memif;
	struct mtk_base_afe_irq *irq;
	u32 status;

	regmap_read(afe->regmap, ASYS_IRQ_STATUS, &status);
	regmap_write(afe->regmap, ASYS_IRQ_CLR, status);

	for (id = 0; id < MT2701_MEMIF_NUM; ++id) {
		memif = &afe->memif[id];
		if (memif->irq_usage < 0)
			continue;

		irq = &afe->irqs[memif->irq_usage];
		if (status & 1 << irq->irq_data->irq_clr_shift)
			snd_pcm_period_elapsed(memif->substream);
	}

	return IRQ_HANDLED;
}