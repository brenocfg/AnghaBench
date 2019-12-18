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
struct snd_pcm {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_subclass; int /*<<< orphan*/  dev_class; scalar_t__ info_flags; int /*<<< orphan*/  private_free; struct snd_ali* private_data; } ;
struct snd_ali {struct snd_pcm** pcm; int /*<<< orphan*/  pci; TYPE_1__* card; } ;
struct ali_pcm_description {int /*<<< orphan*/  name; int /*<<< orphan*/  class; scalar_t__ capture_ops; scalar_t__ playback_ops; int /*<<< orphan*/  capture_num; int /*<<< orphan*/  playback_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SNDRV_PCM_SUBCLASS_GENERIC_MIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_ali_pcm_free ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ali_pcm(struct snd_ali *codec, int device,
		       struct ali_pcm_description *desc)
{
	struct snd_pcm *pcm;
	int err;

	err = snd_pcm_new(codec->card, desc->name, device,
			  desc->playback_num, desc->capture_num, &pcm);
	if (err < 0) {
		dev_err(codec->card->dev,
			"snd_ali_pcm: err called snd_pcm_new.\n");
		return err;
	}
	pcm->private_data = codec;
	pcm->private_free = snd_ali_pcm_free;
	if (desc->playback_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				desc->playback_ops);
	if (desc->capture_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
				desc->capture_ops);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(codec->pci),
					      64*1024, 128*1024);

	pcm->info_flags = 0;
	pcm->dev_class = desc->class;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	strcpy(pcm->name, desc->name);
	codec->pcm[0] = pcm;
	return 0;
}