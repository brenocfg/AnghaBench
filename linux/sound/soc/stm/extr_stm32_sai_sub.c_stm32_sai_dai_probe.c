#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int maxburst; int /*<<< orphan*/  addr_width; scalar_t__ addr; } ;
struct stm32_sai_sub_data {scalar_t__ sync; int /*<<< orphan*/  regmap; int /*<<< orphan*/  synci; int /*<<< orphan*/  synco; int /*<<< orphan*/  np_sync_provider; TYPE_2__* pdata; TYPE_3__ dma_params; scalar_t__ phys_addr; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_5__ {int fifo_size; } ;
struct TYPE_6__ {int (* set_sync ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_UNDEFINED ; 
 scalar_t__ SAI_SYNC_EXTERNAL ; 
 int SAI_XCR1_RX_TX ; 
 int SAI_XCR1_SYNCEN_MASK ; 
 int SAI_XCR1_SYNCEN_SET (scalar_t__) ; 
 int /*<<< orphan*/  STM_SAI_CR1_REGX ; 
 scalar_t__ STM_SAI_DR_REGX ; 
 scalar_t__ STM_SAI_IS_CAPTURE (struct stm32_sai_sub_data*) ; 
 scalar_t__ STM_SAI_IS_PLAYBACK (struct stm32_sai_sub_data*) ; 
 scalar_t__ STM_SAI_PROTOCOL_IS_SPDIF (struct stm32_sai_sub_data*) ; 
 struct stm32_sai_sub_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,TYPE_3__*,TYPE_3__*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_sai_dai_probe(struct snd_soc_dai *cpu_dai)
{
	struct stm32_sai_sub_data *sai = dev_get_drvdata(cpu_dai->dev);
	int cr1 = 0, cr1_mask, ret;

	sai->cpu_dai = cpu_dai;

	sai->dma_params.addr = (dma_addr_t)(sai->phys_addr + STM_SAI_DR_REGX);
	/*
	 * DMA supports 4, 8 or 16 burst sizes. Burst size 4 is the best choice,
	 * as it allows bytes, half-word and words transfers. (See DMA fifos
	 * constraints).
	 */
	sai->dma_params.maxburst = 4;
	if (sai->pdata->conf.fifo_size < 8)
		sai->dma_params.maxburst = 1;
	/* Buswidth will be set by framework at runtime */
	sai->dma_params.addr_width = DMA_SLAVE_BUSWIDTH_UNDEFINED;

	if (STM_SAI_IS_PLAYBACK(sai))
		snd_soc_dai_init_dma_data(cpu_dai, &sai->dma_params, NULL);
	else
		snd_soc_dai_init_dma_data(cpu_dai, NULL, &sai->dma_params);

	/* Next settings are not relevant for spdif mode */
	if (STM_SAI_PROTOCOL_IS_SPDIF(sai))
		return 0;

	cr1_mask = SAI_XCR1_RX_TX;
	if (STM_SAI_IS_CAPTURE(sai))
		cr1 |= SAI_XCR1_RX_TX;

	/* Configure synchronization */
	if (sai->sync == SAI_SYNC_EXTERNAL) {
		/* Configure synchro client and provider */
		ret = sai->pdata->set_sync(sai->pdata, sai->np_sync_provider,
					   sai->synco, sai->synci);
		if (ret)
			return ret;
	}

	cr1_mask |= SAI_XCR1_SYNCEN_MASK;
	cr1 |= SAI_XCR1_SYNCEN_SET(sai->sync);

	return regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX, cr1_mask, cr1);
}