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
struct snd_pcm {int /*<<< orphan*/  name; scalar_t__ info_flags; struct snd_amd7930* private_data; } ;
struct snd_amd7930 {struct snd_pcm* pcm; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  shortname; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_CONTINUOUS ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_amd7930_capture_ops ; 
 int /*<<< orphan*/  snd_amd7930_playback_ops ; 
 int /*<<< orphan*/  snd_dma_continuous_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (TYPE_1__*,char*,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_amd7930_pcm(struct snd_amd7930 *amd)
{
	struct snd_pcm *pcm;
	int err;

	if ((err = snd_pcm_new(amd->card,
			       /* ID */             "sun_amd7930",
			       /* device */         0,
			       /* playback count */ 1,
			       /* capture count */  1, &pcm)) < 0)
		return err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_amd7930_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_amd7930_capture_ops);

	pcm->private_data = amd;
	pcm->info_flags = 0;
	strcpy(pcm->name, amd->card->shortname);
	amd->pcm = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_CONTINUOUS,
					      snd_dma_continuous_data(GFP_KERNEL),
					      64*1024, 64*1024);

	return 0;
}