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
struct via82xx {int multi_devno; int capture_devno; int num_devs; int intr_mask; TYPE_1__* ac97; int /*<<< orphan*/  pci; struct snd_pcm** pcms; TYPE_2__* card; scalar_t__ playback_devno; } ;
struct snd_pcm_chmap {int dummy; } ;
struct snd_pcm {int /*<<< orphan*/  name; struct via82xx* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  shortname; } ;
struct TYPE_3__ {struct snd_pcm_chmap** chmaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV_SG ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  VIA_MAX_BUFSIZE ; 
 int VIA_REG_CAPTURE_8233_STATUS ; 
 int VIA_REG_MULTPLAY_STATUS ; 
 int /*<<< orphan*/  init_viadev (struct via82xx*,int,int,int,int) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int snd_pcm_add_chmap_ctls (struct snd_pcm*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct snd_pcm_chmap**) ; 
 int /*<<< orphan*/  snd_pcm_alt_chmaps ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_pcm_new (TYPE_2__*,int /*<<< orphan*/ ,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_std_chmaps ; 
 int /*<<< orphan*/  snd_via8233_capture_ops ; 
 int /*<<< orphan*/  snd_via8233_multi_ops ; 
 int /*<<< orphan*/  snd_via8233_playback_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_via8233_pcm_new(struct via82xx *chip)
{
	struct snd_pcm *pcm;
	struct snd_pcm_chmap *chmap;
	int i, err;

	chip->playback_devno = 0;	/* x 4 */
	chip->multi_devno = 4;		/* x 1 */
	chip->capture_devno = 5;	/* x 2 */
	chip->num_devs = 7;
	chip->intr_mask = 0x33033333; /* FLAG|EOL for rec0-1, mc, sdx0-3 */

	/* PCM #0:  4 DSX playbacks and 1 capture */
	err = snd_pcm_new(chip->card, chip->card->shortname, 0, 4, 1, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_via8233_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_via8233_capture_ops);
	pcm->private_data = chip;
	strcpy(pcm->name, chip->card->shortname);
	chip->pcms[0] = pcm;
	/* set up playbacks */
	for (i = 0; i < 4; i++)
		init_viadev(chip, i, 0x10 * i, i, 0);
	/* capture */
	init_viadev(chip, chip->capture_devno, VIA_REG_CAPTURE_8233_STATUS, 6, 1);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
					      snd_dma_pci_data(chip->pci),
					      64*1024, VIA_MAX_BUFSIZE);

	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_std_chmaps, 2, 0,
				     &chmap);
	if (err < 0)
		return err;

	/* PCM #1:  multi-channel playback and 2nd capture */
	err = snd_pcm_new(chip->card, chip->card->shortname, 1, 1, 1, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_via8233_multi_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_via8233_capture_ops);
	pcm->private_data = chip;
	strcpy(pcm->name, chip->card->shortname);
	chip->pcms[1] = pcm;
	/* set up playback */
	init_viadev(chip, chip->multi_devno, VIA_REG_MULTPLAY_STATUS, 4, 0);
	/* set up capture */
	init_viadev(chip, chip->capture_devno + 1, VIA_REG_CAPTURE_8233_STATUS + 0x10, 7, 1);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
					      snd_dma_pci_data(chip->pci),
					      64*1024, VIA_MAX_BUFSIZE);

	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_alt_chmaps, 6, 0,
				     &chmap);
	if (err < 0)
		return err;
	chip->ac97->chmaps[SNDRV_PCM_STREAM_PLAYBACK] = chmap;

	return 0;
}