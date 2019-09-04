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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {TYPE_1__* pstr; struct snd_soc_pcm_runtime* private_data; } ;
struct psc_dma_stream {int /*<<< orphan*/ * stream; int /*<<< orphan*/  active; } ;
struct psc_dma {TYPE_3__* psc_regs; int /*<<< orphan*/  imr; struct psc_dma_stream capture; struct psc_dma_stream playback; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  imr; } ;
struct TYPE_6__ {int /*<<< orphan*/  command; TYPE_2__ isr_imr; } ;
struct TYPE_4__ {scalar_t__ stream; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct psc_dma* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psc_dma_close(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct psc_dma *psc_dma = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	struct psc_dma_stream *s;

	dev_dbg(psc_dma->dev, "psc_dma_close(substream=%p)\n", substream);

	if (substream->pstr->stream == SNDRV_PCM_STREAM_CAPTURE)
		s = &psc_dma->capture;
	else
		s = &psc_dma->playback;

	if (!psc_dma->playback.active &&
	    !psc_dma->capture.active) {

		/* Disable all interrupts and reset the PSC */
		out_be16(&psc_dma->psc_regs->isr_imr.imr, psc_dma->imr);
		out_8(&psc_dma->psc_regs->command, 4 << 4); /* reset error */
	}
	s->stream = NULL;
	return 0;
}