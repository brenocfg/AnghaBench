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
struct usb_line6 {TYPE_1__* properties; int /*<<< orphan*/  card; } ;
struct snd_pcm {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_CONTINUOUS ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_dma_continuous_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_line6_capture_ops ; 
 int /*<<< orphan*/  snd_line6_playback_ops ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int snd_line6_new_pcm(struct usb_line6 *line6, struct snd_pcm **pcm_ret)
{
	struct snd_pcm *pcm;
	int err;

	err = snd_pcm_new(line6->card, (char *)line6->properties->name,
			  0, 1, 1, pcm_ret);
	if (err < 0)
		return err;
	pcm = *pcm_ret;
	strcpy(pcm->name, line6->properties->name);

	/* set operators */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_line6_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_line6_capture_ops);

	/* pre-allocation of buffers */
	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_CONTINUOUS,
					      snd_dma_continuous_data
					      (GFP_KERNEL), 64 * 1024,
					      128 * 1024);
	return 0;
}