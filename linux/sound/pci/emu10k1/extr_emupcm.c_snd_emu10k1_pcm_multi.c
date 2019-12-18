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
struct snd_pcm_substream {struct snd_pcm_substream* next; } ;
struct snd_pcm {TYPE_1__* streams; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_subclass; scalar_t__ info_flags; struct snd_emu10k1* private_data; } ;
struct snd_emu10k1 {int /*<<< orphan*/  pci; struct snd_pcm* pcm_multi; int /*<<< orphan*/  card; } ;
struct TYPE_2__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV_SG ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SNDRV_PCM_SUBCLASS_GENERIC_MIX ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_efx_playback_ops ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int snd_emu10k1_pcm_multi(struct snd_emu10k1 *emu, int device)
{
	struct snd_pcm *pcm;
	struct snd_pcm_substream *substream;
	int err;

	if ((err = snd_pcm_new(emu->card, "emu10k1", device, 1, 0, &pcm)) < 0)
		return err;

	pcm->private_data = emu;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_emu10k1_efx_playback_ops);

	pcm->info_flags = 0;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	strcpy(pcm->name, "Multichannel Playback");
	emu->pcm_multi = pcm;

	for (substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream; substream; substream = substream->next)
		snd_pcm_lib_preallocate_pages(substream, SNDRV_DMA_TYPE_DEV_SG,
					      snd_dma_pci_data(emu->pci),
					      64*1024, 64*1024);

	return 0;
}