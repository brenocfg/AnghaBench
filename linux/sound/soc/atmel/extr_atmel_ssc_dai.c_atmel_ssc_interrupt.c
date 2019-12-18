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
typedef  int u32 ;
struct atmel_ssc_info {struct atmel_pcm_dma_params** dma_params; TYPE_1__* ssc; } ;
struct atmel_pcm_dma_params {int /*<<< orphan*/  substream; int /*<<< orphan*/  (* dma_intr_handler ) (int,int /*<<< orphan*/ ) ;TYPE_2__* mask; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int ssc_endx; int ssc_endbuf; } ;
struct TYPE_3__ {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct atmel_pcm_dma_params**) ; 
 int /*<<< orphan*/  IMR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SR ; 
 scalar_t__ ssc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t atmel_ssc_interrupt(int irq, void *dev_id)
{
	struct atmel_ssc_info *ssc_p = dev_id;
	struct atmel_pcm_dma_params *dma_params;
	u32 ssc_sr;
	u32 ssc_substream_mask;
	int i;

	ssc_sr = (unsigned long)ssc_readl(ssc_p->ssc->regs, SR)
			& (unsigned long)ssc_readl(ssc_p->ssc->regs, IMR);

	/*
	 * Loop through the substreams attached to this SSC.  If
	 * a DMA-related interrupt occurred on that substream, call
	 * the DMA interrupt handler function, if one has been
	 * registered in the dma_params structure by the PCM driver.
	 */
	for (i = 0; i < ARRAY_SIZE(ssc_p->dma_params); i++) {
		dma_params = ssc_p->dma_params[i];

		if ((dma_params != NULL) &&
			(dma_params->dma_intr_handler != NULL)) {
			ssc_substream_mask = (dma_params->mask->ssc_endx |
					dma_params->mask->ssc_endbuf);
			if (ssc_sr & ssc_substream_mask) {
				dma_params->dma_intr_handler(ssc_sr,
						dma_params->
						substream);
			}
		}
	}

	return IRQ_HANDLED;
}