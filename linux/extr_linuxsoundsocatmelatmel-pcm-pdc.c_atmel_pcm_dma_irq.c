#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
struct atmel_runtime_data {int period_ptr; int period_size; int dma_buffer_end; int dma_buffer; struct atmel_pcm_dma_params* params; } ;
struct atmel_pcm_dma_params {int pdc_xfer_size; TYPE_4__* pdc; TYPE_3__* ssc; TYPE_2__* mask; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  xncr; int /*<<< orphan*/  xnpr; int /*<<< orphan*/  xcr; int /*<<< orphan*/  xpr; } ;
struct TYPE_7__ {int /*<<< orphan*/  regs; } ;
struct TYPE_6__ {int ssc_endbuf; int pdc_disable; int pdc_enable; int ssc_endx; } ;
struct TYPE_5__ {struct atmel_runtime_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PDC_PTCR ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  pr_warn (char*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  ssc_writex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atmel_pcm_dma_irq(u32 ssc_sr,
	struct snd_pcm_substream *substream)
{
	struct atmel_runtime_data *prtd = substream->runtime->private_data;
	struct atmel_pcm_dma_params *params = prtd->params;
	static int count;

	count++;

	if (ssc_sr & params->mask->ssc_endbuf) {
		pr_warn("atmel-pcm: buffer %s on %s (SSC_SR=%#x, count=%d)\n",
				substream->stream == SNDRV_PCM_STREAM_PLAYBACK
				? "underrun" : "overrun",
				params->name, ssc_sr, count);

		/* re-start the PDC */
		ssc_writex(params->ssc->regs, ATMEL_PDC_PTCR,
			   params->mask->pdc_disable);
		prtd->period_ptr += prtd->period_size;
		if (prtd->period_ptr >= prtd->dma_buffer_end)
			prtd->period_ptr = prtd->dma_buffer;

		ssc_writex(params->ssc->regs, params->pdc->xpr,
			   prtd->period_ptr);
		ssc_writex(params->ssc->regs, params->pdc->xcr,
			   prtd->period_size / params->pdc_xfer_size);
		ssc_writex(params->ssc->regs, ATMEL_PDC_PTCR,
			   params->mask->pdc_enable);
	}

	if (ssc_sr & params->mask->ssc_endx) {
		/* Load the PDC next pointer and counter registers */
		prtd->period_ptr += prtd->period_size;
		if (prtd->period_ptr >= prtd->dma_buffer_end)
			prtd->period_ptr = prtd->dma_buffer;

		ssc_writex(params->ssc->regs, params->pdc->xnpr,
			   prtd->period_ptr);
		ssc_writex(params->ssc->regs, params->pdc->xncr,
			   prtd->period_size / params->pdc_xfer_size);
	}

	snd_pcm_period_elapsed(substream);
}