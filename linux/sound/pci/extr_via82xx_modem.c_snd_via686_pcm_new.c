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
struct via82xx_modem {int capture_devno; int num_devs; int intr_mask; int /*<<< orphan*/  pci; struct snd_pcm** pcms; TYPE_1__* card; scalar_t__ playback_devno; } ;
struct snd_pcm {int /*<<< orphan*/  name; struct via82xx_modem* private_data; int /*<<< orphan*/  dev_class; } ;
struct TYPE_2__ {int /*<<< orphan*/  shortname; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV_SG ; 
 int /*<<< orphan*/  SNDRV_PCM_CLASS_MODEM ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  VIA_REG_MI_STATUS ; 
 int /*<<< orphan*/  VIA_REG_MO_STATUS ; 
 int /*<<< orphan*/  init_viadev (struct via82xx_modem*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_via686_capture_ops ; 
 int /*<<< orphan*/  snd_via686_playback_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_via686_pcm_new(struct via82xx_modem *chip)
{
	struct snd_pcm *pcm;
	int err;

	chip->playback_devno = 0;
	chip->capture_devno = 1;
	chip->num_devs = 2;
	chip->intr_mask = 0x330000; /* FLAGS | EOL for MR, MW */

	err = snd_pcm_new(chip->card, chip->card->shortname, 0, 1, 1, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_via686_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_via686_capture_ops);
	pcm->dev_class = SNDRV_PCM_CLASS_MODEM;
	pcm->private_data = chip;
	strcpy(pcm->name, chip->card->shortname);
	chip->pcms[0] = pcm;
	init_viadev(chip, 0, VIA_REG_MO_STATUS, 0);
	init_viadev(chip, 1, VIA_REG_MI_STATUS, 1);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
					      snd_dma_pci_data(chip->pci),
					      64*1024, 128*1024);
	return 0;
}