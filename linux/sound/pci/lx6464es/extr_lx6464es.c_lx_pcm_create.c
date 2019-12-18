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
typedef  int u32 ;
struct snd_pcm {int nonatomic; int /*<<< orphan*/  name; scalar_t__ info_flags; struct lx6464es* private_data; } ;
struct TYPE_2__ {int is_capture; } ;
struct lx6464es {TYPE_1__ capture_stream; struct snd_pcm* pcm; int /*<<< orphan*/  pci; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int MAX_STREAM_BUFFER ; 
 int MICROBLAZE_IBL_MAX ; 
 int PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ card_name ; 
 int /*<<< orphan*/  lx_ops_capture ; 
 int /*<<< orphan*/  lx_ops_playback ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lx_pcm_create(struct lx6464es *chip)
{
	int err;
	struct snd_pcm *pcm;

	u32 size = 64 *		     /* channels */
		3 *		     /* 24 bit samples */
		MAX_STREAM_BUFFER *  /* periods */
		MICROBLAZE_IBL_MAX * /* frames per period */
		2;		     /* duplex */

	size = PAGE_ALIGN(size);

	/* hardcoded device name & channel count */
	err = snd_pcm_new(chip->card, (char *)card_name, 0,
			  1, 1, &pcm);
	if (err < 0)
		return err;

	pcm->private_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &lx_ops_playback);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &lx_ops_capture);

	pcm->info_flags = 0;
	pcm->nonatomic = true;
	strcpy(pcm->name, card_name);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(chip->pci),
					      size, size);

	chip->pcm = pcm;
	chip->capture_stream.is_capture = 1;

	return 0;
}