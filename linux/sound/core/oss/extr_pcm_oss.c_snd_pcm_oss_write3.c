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
struct snd_pcm_substream {int /*<<< orphan*/  pcm; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_1__* status; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  int snd_pcm_sframes_t ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EPIPE ; 
 int ESTRPIPE ; 
 scalar_t__ SNDRV_PCM_STATE_PREPARED ; 
 scalar_t__ SNDRV_PCM_STATE_SUSPENDED ; 
 scalar_t__ SNDRV_PCM_STATE_XRUN ; 
 int __snd_pcm_lib_xfer (struct snd_pcm_substream*,void*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int snd_pcm_oss_prepare (struct snd_pcm_substream*) ; 

snd_pcm_sframes_t snd_pcm_oss_write3(struct snd_pcm_substream *substream, const char *ptr, snd_pcm_uframes_t frames, int in_kernel)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int ret;
	while (1) {
		if (runtime->status->state == SNDRV_PCM_STATE_XRUN ||
		    runtime->status->state == SNDRV_PCM_STATE_SUSPENDED) {
#ifdef OSS_DEBUG
			pcm_dbg(substream->pcm,
				"pcm_oss: write: recovering from %s\n",
				runtime->status->state == SNDRV_PCM_STATE_XRUN ?
				"XRUN" : "SUSPEND");
#endif
			ret = snd_pcm_oss_prepare(substream);
			if (ret < 0)
				break;
		}
		ret = __snd_pcm_lib_xfer(substream, (void *)ptr, true,
					 frames, in_kernel);
		if (ret != -EPIPE && ret != -ESTRPIPE)
			break;
		/* test, if we can't store new data, because the stream */
		/* has not been started */
		if (runtime->status->state == SNDRV_PCM_STATE_PREPARED)
			return -EAGAIN;
	}
	return ret;
}