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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ dma_bytes; scalar_t__ dma_addr; int /*<<< orphan*/ * dma_area; struct snd_cs46xx_pcm* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * area; } ;
struct snd_cs46xx_pcm {TYPE_1__ hw_buf; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cs46xx_playback_hw_free(struct snd_pcm_substream *substream)
{
	/*struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);*/
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_cs46xx_pcm *cpcm;

	cpcm = runtime->private_data;

	/* if play_back open fails, then this function
	   is called and cpcm can actually be NULL here */
	if (!cpcm) return -ENXIO;

	if (runtime->dma_area != cpcm->hw_buf.area)
		snd_pcm_lib_free_pages(substream);
    
	runtime->dma_area = NULL;
	runtime->dma_addr = 0;
	runtime->dma_bytes = 0;

	return 0;
}