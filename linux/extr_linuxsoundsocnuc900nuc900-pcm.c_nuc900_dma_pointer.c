#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned long dma_addr; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  bytes_to_frames (struct snd_pcm_runtime*,unsigned long) ; 
 int /*<<< orphan*/  nuc900_dma_getposition (struct snd_pcm_substream*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static snd_pcm_uframes_t nuc900_dma_pointer(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	dma_addr_t src, dst;
	unsigned long res;

	nuc900_dma_getposition(substream, &src, &dst);

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		res = dst - runtime->dma_addr;
	else
		res = src - runtime->dma_addr;

	return bytes_to_frames(substream->runtime, res);
}