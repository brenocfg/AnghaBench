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
struct snd_pcm {int /*<<< orphan*/  name; scalar_t__ info_flags; struct cs5535audio* private_data; } ;
struct cs5535audio {struct snd_pcm* pcm; int /*<<< orphan*/  pci; TYPE_1__* dmas; int /*<<< orphan*/  card; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 size_t CS5535AUDIO_DMA_CAPTURE ; 
 size_t CS5535AUDIO_DMA_PLAYBACK ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_cs5535audio_capture_dma_ops ; 
 int /*<<< orphan*/  snd_cs5535audio_capture_ops ; 
 int /*<<< orphan*/  snd_cs5535audio_playback_dma_ops ; 
 int /*<<< orphan*/  snd_cs5535audio_playback_ops ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int snd_cs5535audio_pcm(struct cs5535audio *cs5535au)
{
	struct snd_pcm *pcm;
	int err;

	err = snd_pcm_new(cs5535au->card, "CS5535 Audio", 0, 1, 1, &pcm);
	if (err < 0)
		return err;

	cs5535au->dmas[CS5535AUDIO_DMA_PLAYBACK].ops =
					&snd_cs5535audio_playback_dma_ops;
	cs5535au->dmas[CS5535AUDIO_DMA_CAPTURE].ops =
					&snd_cs5535audio_capture_dma_ops;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					&snd_cs5535audio_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
					&snd_cs5535audio_capture_ops);

	pcm->private_data = cs5535au;
	pcm->info_flags = 0;
	strcpy(pcm->name, "CS5535 Audio");

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					snd_dma_pci_data(cs5535au->pci),
					64*1024, 128*1024);
	cs5535au->pcm = pcm;

	return 0;
}