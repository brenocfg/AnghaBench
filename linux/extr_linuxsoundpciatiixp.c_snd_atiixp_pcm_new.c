#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_chmap {int /*<<< orphan*/  channel_mask; } ;
struct snd_pcm {int /*<<< orphan*/  name; struct atiixp* private_data; } ;
struct snd_ac97_bus {TYPE_3__* pcms; } ;
struct atiixp {int max_channels; TYPE_4__** ac97; int /*<<< orphan*/  pci; struct snd_pcm** pcmdevs; scalar_t__ spdif_over_aclink; int /*<<< orphan*/  card; TYPE_3__** pcms; TYPE_1__* dmas; struct snd_ac97_bus* ac97_bus; } ;
struct TYPE_8__ {struct snd_pcm_chmap** chmaps; } ;
struct TYPE_7__ {scalar_t__ rates; TYPE_2__* r; } ;
struct TYPE_6__ {int slots; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EXTENDED_STATUS ; 
 int AC97_SLOT_LFE ; 
 int AC97_SLOT_PCM_SLEFT ; 
 size_t ATI_DMA_CAPTURE ; 
 size_t ATI_DMA_PLAYBACK ; 
 size_t ATI_DMA_SPDIF ; 
 size_t ATI_PCMDEV_ANALOG ; 
 size_t ATI_PCMDEV_DIGITAL ; 
 size_t ATI_PCM_OUT ; 
 size_t ATI_PCM_SPDIF ; 
 int NUM_ATI_CODECS ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 scalar_t__ SNDRV_PCM_RATE_48000 ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SND_PCM_CHMAP_MASK_2468 ; 
 int /*<<< orphan*/  atiixp_pcm_defs ; 
 int snd_ac97_pcm_assign (struct snd_ac97_bus*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_atiixp_capture_dma_ops ; 
 int /*<<< orphan*/  snd_atiixp_capture_ops ; 
 int /*<<< orphan*/  snd_atiixp_playback_dma_ops ; 
 int /*<<< orphan*/  snd_atiixp_playback_ops ; 
 int /*<<< orphan*/  snd_atiixp_spdif_dma_ops ; 
 int /*<<< orphan*/  snd_atiixp_spdif_ops ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int snd_pcm_add_chmap_ctls (struct snd_pcm*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct snd_pcm_chmap**) ; 
 int /*<<< orphan*/  snd_pcm_alt_chmaps ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,size_t,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_atiixp_pcm_new(struct atiixp *chip)
{
	struct snd_pcm *pcm;
	struct snd_pcm_chmap *chmap;
	struct snd_ac97_bus *pbus = chip->ac97_bus;
	int err, i, num_pcms;

	/* initialize constants */
	chip->dmas[ATI_DMA_PLAYBACK].ops = &snd_atiixp_playback_dma_ops;
	chip->dmas[ATI_DMA_CAPTURE].ops = &snd_atiixp_capture_dma_ops;
	if (! chip->spdif_over_aclink)
		chip->dmas[ATI_DMA_SPDIF].ops = &snd_atiixp_spdif_dma_ops;

	/* assign AC97 pcm */
	if (chip->spdif_over_aclink)
		num_pcms = 3;
	else
		num_pcms = 2;
	err = snd_ac97_pcm_assign(pbus, num_pcms, atiixp_pcm_defs);
	if (err < 0)
		return err;
	for (i = 0; i < num_pcms; i++)
		chip->pcms[i] = &pbus->pcms[i];

	chip->max_channels = 2;
	if (pbus->pcms[ATI_PCM_OUT].r[0].slots & (1 << AC97_SLOT_PCM_SLEFT)) {
		if (pbus->pcms[ATI_PCM_OUT].r[0].slots & (1 << AC97_SLOT_LFE))
			chip->max_channels = 6;
		else
			chip->max_channels = 4;
	}

	/* PCM #0: analog I/O */
	err = snd_pcm_new(chip->card, "ATI IXP AC97",
			  ATI_PCMDEV_ANALOG, 1, 1, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_atiixp_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_atiixp_capture_ops);
	pcm->private_data = chip;
	strcpy(pcm->name, "ATI IXP AC97");
	chip->pcmdevs[ATI_PCMDEV_ANALOG] = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(chip->pci),
					      64*1024, 128*1024);

	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_alt_chmaps, chip->max_channels, 0,
				     &chmap);
	if (err < 0)
		return err;
	chmap->channel_mask = SND_PCM_CHMAP_MASK_2468;
	chip->ac97[0]->chmaps[SNDRV_PCM_STREAM_PLAYBACK] = chmap;

	/* no SPDIF support on codec? */
	if (chip->pcms[ATI_PCM_SPDIF] && ! chip->pcms[ATI_PCM_SPDIF]->rates)
		return 0;
		
	/* FIXME: non-48k sample rate doesn't work on my test machine with AD1888 */
	if (chip->pcms[ATI_PCM_SPDIF])
		chip->pcms[ATI_PCM_SPDIF]->rates = SNDRV_PCM_RATE_48000;

	/* PCM #1: spdif playback */
	err = snd_pcm_new(chip->card, "ATI IXP IEC958",
			  ATI_PCMDEV_DIGITAL, 1, 0, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_atiixp_spdif_ops);
	pcm->private_data = chip;
	if (chip->spdif_over_aclink)
		strcpy(pcm->name, "ATI IXP IEC958 (AC97)");
	else
		strcpy(pcm->name, "ATI IXP IEC958 (Direct)");
	chip->pcmdevs[ATI_PCMDEV_DIGITAL] = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(chip->pci),
					      64*1024, 128*1024);

	/* pre-select AC97 SPDIF slots 10/11 */
	for (i = 0; i < NUM_ATI_CODECS; i++) {
		if (chip->ac97[i])
			snd_ac97_update_bits(chip->ac97[i],
					     AC97_EXTENDED_STATUS,
					     0x03 << 4, 0x03 << 4);
	}

	return 0;
}