#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_oss_file {struct snd_pcm_substream** streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_START ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_pcm_kernel_ioctl (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snd_pcm_oss_make_ready (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_oss_post(struct snd_pcm_oss_file *pcm_oss_file)
{
	struct snd_pcm_substream *substream;
	int err;

	substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
	if (substream != NULL) {
		if ((err = snd_pcm_oss_make_ready(substream)) < 0)
			return err;
		snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_START, NULL);
	}
	/* note: all errors from the start action are ignored */
	/* OSS apps do not know, how to handle them */
	return 0;
}