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
struct snd_pcm_chmap_elem {int dummy; } ;
struct snd_pcm {int /*<<< orphan*/  name; scalar_t__ info_flags; struct emu10k1x* private_data; } ;
struct emu10k1x {int /*<<< orphan*/  pci; struct snd_pcm* pcm; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 struct snd_pcm_chmap_elem* clfe_map ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1x_capture_ops ; 
 int /*<<< orphan*/  snd_emu10k1x_playback_ops ; 
 int snd_pcm_add_chmap_ctls (struct snd_pcm*,int /*<<< orphan*/ ,struct snd_pcm_chmap_elem const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_pcm_chmap_elem* snd_pcm_std_chmaps ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct snd_pcm_chmap_elem* surround_map ; 

__attribute__((used)) static int snd_emu10k1x_pcm(struct emu10k1x *emu, int device)
{
	struct snd_pcm *pcm;
	const struct snd_pcm_chmap_elem *map = NULL;
	int err;
	int capture = 0;
  
	if (device == 0)
		capture = 1;
	
	if ((err = snd_pcm_new(emu->card, "emu10k1x", device, 1, capture, &pcm)) < 0)
		return err;
  
	pcm->private_data = emu;
	
	switch(device) {
	case 0:
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_emu10k1x_playback_ops);
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_emu10k1x_capture_ops);
		break;
	case 1:
	case 2:
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_emu10k1x_playback_ops);
		break;
	}

	pcm->info_flags = 0;
	switch(device) {
	case 0:
		strcpy(pcm->name, "EMU10K1X Front");
		map = snd_pcm_std_chmaps;
		break;
	case 1:
		strcpy(pcm->name, "EMU10K1X Rear");
		map = surround_map;
		break;
	case 2:
		strcpy(pcm->name, "EMU10K1X Center/LFE");
		map = clfe_map;
		break;
	}
	emu->pcm = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(emu->pci), 
					      32*1024, 32*1024);
  
	return snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK, map, 2,
				     1 << 2, NULL);
}