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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; TYPE_1__* pstr; struct snd_soc_pcm_runtime* private_data; } ;
struct psc_dma_stream {int period_current; int period_bytes; } ;
struct psc_dma {struct psc_dma_stream playback; struct psc_dma_stream capture; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  int dma_addr_t ;
struct TYPE_2__ {scalar_t__ stream; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,int) ; 
 struct psc_dma* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t
psc_dma_pointer(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct psc_dma *psc_dma = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	struct psc_dma_stream *s;
	dma_addr_t count;

	if (substream->pstr->stream == SNDRV_PCM_STREAM_CAPTURE)
		s = &psc_dma->capture;
	else
		s = &psc_dma->playback;

	count = s->period_current * s->period_bytes;

	return bytes_to_frames(substream->runtime, count);
}