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
struct snd_pcm_substream {TYPE_1__* pstr; } ;
struct psc_dma_stream {int dummy; } ;
struct psc_dma {struct psc_dma_stream playback; struct psc_dma_stream capture; } ;
struct TYPE_2__ {scalar_t__ stream; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 

__attribute__((used)) static inline struct psc_dma_stream *
to_psc_dma_stream(struct snd_pcm_substream *substream, struct psc_dma *psc_dma)
{
	if (substream->pstr->stream == SNDRV_PCM_STREAM_CAPTURE)
		return &psc_dma->capture;
	return &psc_dma->playback;
}