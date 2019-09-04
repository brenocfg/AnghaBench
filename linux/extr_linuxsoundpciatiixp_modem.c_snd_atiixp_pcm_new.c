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
struct snd_pcm {int /*<<< orphan*/  name; struct atiixp_modem* private_data; int /*<<< orphan*/  dev_class; } ;
struct atiixp_modem {int /*<<< orphan*/  pci; struct snd_pcm** pcmdevs; int /*<<< orphan*/  card; TYPE_1__* dmas; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 size_t ATI_DMA_CAPTURE ; 
 size_t ATI_DMA_PLAYBACK ; 
 size_t ATI_PCMDEV_ANALOG ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_CLASS_MODEM ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_atiixp_capture_dma_ops ; 
 int /*<<< orphan*/  snd_atiixp_capture_ops ; 
 int /*<<< orphan*/  snd_atiixp_playback_dma_ops ; 
 int /*<<< orphan*/  snd_atiixp_playback_ops ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,size_t,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_atiixp_pcm_new(struct atiixp_modem *chip)
{
	struct snd_pcm *pcm;
	int err;

	/* initialize constants */
	chip->dmas[ATI_DMA_PLAYBACK].ops = &snd_atiixp_playback_dma_ops;
	chip->dmas[ATI_DMA_CAPTURE].ops = &snd_atiixp_capture_dma_ops;

	/* PCM #0: analog I/O */
	err = snd_pcm_new(chip->card, "ATI IXP MC97", ATI_PCMDEV_ANALOG, 1, 1, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_atiixp_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_atiixp_capture_ops);
	pcm->dev_class = SNDRV_PCM_CLASS_MODEM;
	pcm->private_data = chip;
	strcpy(pcm->name, "ATI IXP MC97");
	chip->pcmdevs[ATI_PCMDEV_ANALOG] = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(chip->pci),
					      64*1024, 128*1024);

	return 0;
}