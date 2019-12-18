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
struct snd_pcm_substream {TYPE_1__* ops; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned int channels; TYPE_2__* status; } ;
struct snd_pcm_channel_info {unsigned int channel; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {int (* ioctl ) (struct snd_pcm_substream*,int /*<<< orphan*/ ,struct snd_pcm_channel_info*) ;} ;

/* Variables and functions */
 int EBADFD ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_IOCTL1_CHANNEL_INFO ; 
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 int /*<<< orphan*/  memset (struct snd_pcm_channel_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 
 int stub1 (struct snd_pcm_substream*,int /*<<< orphan*/ ,struct snd_pcm_channel_info*) ; 

__attribute__((used)) static int snd_pcm_channel_info(struct snd_pcm_substream *substream,
				struct snd_pcm_channel_info * info)
{
	struct snd_pcm_runtime *runtime;
	unsigned int channel;
	
	channel = info->channel;
	runtime = substream->runtime;
	snd_pcm_stream_lock_irq(substream);
	if (runtime->status->state == SNDRV_PCM_STATE_OPEN) {
		snd_pcm_stream_unlock_irq(substream);
		return -EBADFD;
	}
	snd_pcm_stream_unlock_irq(substream);
	if (channel >= runtime->channels)
		return -EINVAL;
	memset(info, 0, sizeof(*info));
	info->channel = channel;
	return substream->ops->ioctl(substream, SNDRV_PCM_IOCTL1_CHANNEL_INFO, info);
}