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
struct TYPE_4__ {scalar_t__ entries; } ;
struct snd_trident {scalar_t__ device; int /*<<< orphan*/  pci; TYPE_2__ tlb; struct snd_pcm* foldback; int /*<<< orphan*/  card; } ;
struct snd_pcm_substream {int /*<<< orphan*/  name; struct snd_pcm_substream* next; } ;
struct snd_pcm {TYPE_1__* streams; int /*<<< orphan*/  name; scalar_t__ info_flags; struct snd_trident* private_data; } ;
struct TYPE_3__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV_SG ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 scalar_t__ TRIDENT_DEVICE_ID_NX ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_trident_foldback_ops ; 
 int /*<<< orphan*/  snd_trident_nx_foldback_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int snd_trident_foldback_pcm(struct snd_trident *trident, int device)
{
	struct snd_pcm *foldback;
	int err;
	int num_chan = 3;
	struct snd_pcm_substream *substream;

	if (trident->device == TRIDENT_DEVICE_ID_NX)
		num_chan = 4;
	if ((err = snd_pcm_new(trident->card, "trident_dx_nx", device, 0, num_chan, &foldback)) < 0)
		return err;

	foldback->private_data = trident;
	if (trident->tlb.entries)
		snd_pcm_set_ops(foldback, SNDRV_PCM_STREAM_CAPTURE, &snd_trident_nx_foldback_ops);
	else
		snd_pcm_set_ops(foldback, SNDRV_PCM_STREAM_CAPTURE, &snd_trident_foldback_ops);
	foldback->info_flags = 0;
	strcpy(foldback->name, "Trident 4DWave");
	substream = foldback->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	strcpy(substream->name, "Front Mixer");
	substream = substream->next;
	strcpy(substream->name, "Reverb Mixer");
	substream = substream->next;
	strcpy(substream->name, "Chorus Mixer");
	if (num_chan == 4) {
		substream = substream->next;
		strcpy(substream->name, "Second AC'97 ADC");
	}
	trident->foldback = foldback;

	if (trident->tlb.entries)
		snd_pcm_lib_preallocate_pages_for_all(foldback, SNDRV_DMA_TYPE_DEV_SG,
						      snd_dma_pci_data(trident->pci), 0, 128*1024);
	else
		snd_pcm_lib_preallocate_pages_for_all(foldback, SNDRV_DMA_TYPE_DEV,
						      snd_dma_pci_data(trident->pci), 64*1024, 128*1024);

	return 0;
}