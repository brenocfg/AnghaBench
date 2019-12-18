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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_bytes; struct gus_pcm_private* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mem_alloc; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;
struct snd_gf1_mem_block {int /*<<< orphan*/  ptr; } ;
struct gus_pcm_private {int voices; TYPE_2__** pvoices; int /*<<< orphan*/  gus; int /*<<< orphan*/  memory; } ;
struct TYPE_4__ {struct gus_pcm_private* private_data; void* volume_change; void* handler_volume; void* handler_wave; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_GF1_MEM_OWNER_DRIVER ; 
 int /*<<< orphan*/  SNDRV_GF1_VOICE_TYPE_PCM ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 void* snd_gf1_alloc_voice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_free_voice (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct snd_gf1_mem_block* snd_gf1_mem_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_gf1_mem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* snd_gf1_pcm_interrupt_volume ; 
 void* snd_gf1_pcm_interrupt_wave ; 
 void* snd_gf1_pcm_volume_change ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_gus_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_gf1_pcm_playback_hw_params(struct snd_pcm_substream *substream,
					  struct snd_pcm_hw_params *hw_params)
{
	struct snd_gus_card *gus = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct gus_pcm_private *pcmp = runtime->private_data;
	int err;
	
	if ((err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params))) < 0)
		return err;
	if (err > 0) {	/* change */
		struct snd_gf1_mem_block *block;
		if (pcmp->memory > 0) {
			snd_gf1_mem_free(&gus->gf1.mem_alloc, pcmp->memory);
			pcmp->memory = 0;
		}
		if ((block = snd_gf1_mem_alloc(&gus->gf1.mem_alloc,
		                               SNDRV_GF1_MEM_OWNER_DRIVER,
					       "GF1 PCM",
		                               runtime->dma_bytes, 1, 32,
		                               NULL)) == NULL)
			return -ENOMEM;
		pcmp->memory = block->ptr;
	}
	pcmp->voices = params_channels(hw_params);
	if (pcmp->pvoices[0] == NULL) {
		if ((pcmp->pvoices[0] = snd_gf1_alloc_voice(pcmp->gus, SNDRV_GF1_VOICE_TYPE_PCM, 0, 0)) == NULL)
			return -ENOMEM;
		pcmp->pvoices[0]->handler_wave = snd_gf1_pcm_interrupt_wave;
		pcmp->pvoices[0]->handler_volume = snd_gf1_pcm_interrupt_volume;
		pcmp->pvoices[0]->volume_change = snd_gf1_pcm_volume_change;
		pcmp->pvoices[0]->private_data = pcmp;
	}
	if (pcmp->voices > 1 && pcmp->pvoices[1] == NULL) {
		if ((pcmp->pvoices[1] = snd_gf1_alloc_voice(pcmp->gus, SNDRV_GF1_VOICE_TYPE_PCM, 0, 0)) == NULL)
			return -ENOMEM;
		pcmp->pvoices[1]->handler_wave = snd_gf1_pcm_interrupt_wave;
		pcmp->pvoices[1]->handler_volume = snd_gf1_pcm_interrupt_volume;
		pcmp->pvoices[1]->volume_change = snd_gf1_pcm_volume_change;
		pcmp->pvoices[1]->private_data = pcmp;
	} else if (pcmp->voices == 1) {
		if (pcmp->pvoices[1]) {
			snd_gf1_free_voice(pcmp->gus, pcmp->pvoices[1]);
			pcmp->pvoices[1] = NULL;
		}
	}
	return 0;
}