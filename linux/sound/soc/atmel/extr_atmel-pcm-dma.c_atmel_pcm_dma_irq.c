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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct atmel_pcm_dma_params {TYPE_2__* ssc; TYPE_1__* mask; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  regs; } ;
struct TYPE_3__ {int ssc_error; int /*<<< orphan*/  ssc_disable; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SSC_CR ; 
 int /*<<< orphan*/  SSC_RHR ; 
 int /*<<< orphan*/  SSC_SR ; 
 int /*<<< orphan*/  pr_warn (char*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_pcm_running (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (struct snd_pcm_substream*) ; 
 struct atmel_pcm_dma_params* snd_soc_dai_get_dma_data (int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  ssc_readx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssc_writex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_pcm_dma_irq(u32 ssc_sr,
	struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct atmel_pcm_dma_params *prtd;

	prtd = snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);

	if (ssc_sr & prtd->mask->ssc_error) {
		if (snd_pcm_running(substream))
			pr_warn("atmel-pcm: buffer %s on %s (SSC_SR=%#x)\n",
				substream->stream == SNDRV_PCM_STREAM_PLAYBACK
				? "underrun" : "overrun", prtd->name,
				ssc_sr);

		/* stop RX and capture: will be enabled again at restart */
		ssc_writex(prtd->ssc->regs, SSC_CR, prtd->mask->ssc_disable);
		snd_pcm_stop_xrun(substream);

		/* now drain RHR and read status to remove xrun condition */
		ssc_readx(prtd->ssc->regs, SSC_RHR);
		ssc_readx(prtd->ssc->regs, SSC_SR);
	}
}