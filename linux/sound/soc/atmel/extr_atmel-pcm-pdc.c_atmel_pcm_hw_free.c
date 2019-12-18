#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct atmel_runtime_data {struct atmel_pcm_dma_params* params; } ;
struct atmel_pcm_dma_params {int /*<<< orphan*/ * dma_intr_handler; TYPE_3__* mask; TYPE_2__* ssc; } ;
struct TYPE_6__ {int /*<<< orphan*/  pdc_disable; } ;
struct TYPE_5__ {int /*<<< orphan*/  regs; } ;
struct TYPE_4__ {struct atmel_runtime_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSC_PDC_PTCR ; 
 int /*<<< orphan*/  ssc_writex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct atmel_runtime_data *prtd = substream->runtime->private_data;
	struct atmel_pcm_dma_params *params = prtd->params;

	if (params != NULL) {
		ssc_writex(params->ssc->regs, SSC_PDC_PTCR,
			   params->mask->pdc_disable);
		prtd->params->dma_intr_handler = NULL;
	}

	return 0;
}