#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_chmap {int /*<<< orphan*/  channel_mask; } ;
struct snd_pcm {char* name; scalar_t__ info_flags; struct intel8x0* private_data; } ;
struct intel8x0 {TYPE_1__** ac97; scalar_t__ multi4; scalar_t__ multi6; scalar_t__ multi8; int /*<<< orphan*/  pci; struct snd_pcm** pcm; TYPE_3__* card; } ;
struct ich_pcm_table {char* suffix; TYPE_2__* playback_ops; int /*<<< orphan*/  prealloc_max_size; int /*<<< orphan*/  prealloc_size; TYPE_2__* capture_ops; } ;
struct TYPE_6__ {char* shortname; } ;
struct TYPE_5__ {scalar_t__ open; } ;
struct TYPE_4__ {struct snd_pcm_chmap** chmaps; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SND_PCM_CHMAP_MASK_2468 ; 
 int /*<<< orphan*/  intel8x0_dma_type (struct intel8x0*) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_intel8x0_playback_open ; 
 int snd_pcm_add_chmap_ctls (struct snd_pcm*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct snd_pcm_chmap**) ; 
 int /*<<< orphan*/  snd_pcm_alt_chmaps ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_new (TYPE_3__*,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int snd_intel8x0_pcm1(struct intel8x0 *chip, int device,
			     struct ich_pcm_table *rec)
{
	struct snd_pcm *pcm;
	int err;
	char name[32];

	if (rec->suffix)
		sprintf(name, "Intel ICH - %s", rec->suffix);
	else
		strcpy(name, "Intel ICH");
	err = snd_pcm_new(chip->card, name, device,
			  rec->playback_ops ? 1 : 0,
			  rec->capture_ops ? 1 : 0, &pcm);
	if (err < 0)
		return err;

	if (rec->playback_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, rec->playback_ops);
	if (rec->capture_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, rec->capture_ops);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	if (rec->suffix)
		sprintf(pcm->name, "%s - %s", chip->card->shortname, rec->suffix);
	else
		strcpy(pcm->name, chip->card->shortname);
	chip->pcm[device] = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, intel8x0_dma_type(chip),
					      snd_dma_pci_data(chip->pci),
					      rec->prealloc_size, rec->prealloc_max_size);

	if (rec->playback_ops &&
	    rec->playback_ops->open == snd_intel8x0_playback_open) {
		struct snd_pcm_chmap *chmap;
		int chs = 2;
		if (chip->multi8)
			chs = 8;
		else if (chip->multi6)
			chs = 6;
		else if (chip->multi4)
			chs = 4;
		err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					     snd_pcm_alt_chmaps, chs, 0,
					     &chmap);
		if (err < 0)
			return err;
		chmap->channel_mask = SND_PCM_CHMAP_MASK_2468;
		chip->ac97[0]->chmaps[SNDRV_PCM_STREAM_PLAYBACK] = chmap;
	}

	return 0;
}