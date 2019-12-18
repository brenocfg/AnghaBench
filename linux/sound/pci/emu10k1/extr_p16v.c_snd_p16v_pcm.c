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
struct snd_emu10k1 {int p16v_device_offset; int /*<<< orphan*/  pci; struct snd_pcm* pcm_p16v; int /*<<< orphan*/  card; } ;
struct TYPE_2__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SNDRV_PCM_SUBCLASS_GENERIC_MIX ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_p16v_capture_ops ; 
 int /*<<< orphan*/  snd_p16v_playback_front_ops ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int snd_p16v_pcm(struct snd_emu10k1 *emu, int device)
{
	struct snd_pcm *pcm;
	struct snd_pcm_substream *substream;
	int err;
        int capture=1;
  
	/* dev_dbg(emu->card->dev, "snd_p16v_pcm called. device=%d\n", device); */
	emu->p16v_device_offset = device;

	if ((err = snd_pcm_new(emu->card, "p16v", device, 1, capture, &pcm)) < 0)
		return err;
  
	pcm->private_data = emu;
	// Single playback 8 channel device.
	// Single capture 2 channel device.
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_p16v_playback_front_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_p16v_capture_ops);

	pcm->info_flags = 0;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	strcpy(pcm->name, "p16v");
	emu->pcm_p16v = pcm;

	for(substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream; 
	    substream; 
	    substream = substream->next) {
		snd_pcm_lib_preallocate_pages(substream, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(emu->pci),
					      (65536 - 64) * 8,
					      (65536 - 64) * 8);
		/*
		dev_dbg(emu->card->dev,
			   "preallocate playback substream: err=%d\n", err);
		*/
	}

	for (substream = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream; 
	      substream; 
	      substream = substream->next) {
		snd_pcm_lib_preallocate_pages(substream, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(emu->pci),
					      65536 - 64, 65536 - 64);
		/*
		dev_dbg(emu->card->dev,
			   "preallocate capture substream: err=%d\n", err);
		*/
	}
  
	return 0;
}