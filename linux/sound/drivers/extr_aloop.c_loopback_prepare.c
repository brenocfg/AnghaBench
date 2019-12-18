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
struct snd_pcm_substream {int stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int rate; int buffer_size; int period_size; int /*<<< orphan*/  dma_area; int /*<<< orphan*/  format; struct loopback_pcm* private_data; } ;
struct loopback_pcm {int pcm_bps; int pcm_salign; TYPE_1__* loopback; void* pcm_period_size; scalar_t__ period_update_pending; scalar_t__ irq_pos; void* pcm_buffer_size; void* silent_size; scalar_t__ buf_pos; struct loopback_cable* cable; } ;
struct loopback_cable {int valid; } ;
struct TYPE_4__ {scalar_t__ notify; } ;
struct TYPE_3__ {int /*<<< orphan*/  cable_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 void* frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 TYPE_2__* get_setup (struct loopback_pcm*) ; 
 int /*<<< orphan*/  loopback_timer_stop_sync (struct loopback_pcm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  params_change (struct snd_pcm_substream*) ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_format_set_silence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int loopback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct loopback_pcm *dpcm = runtime->private_data;
	struct loopback_cable *cable = dpcm->cable;
	int bps, salign;

	loopback_timer_stop_sync(dpcm);

	salign = (snd_pcm_format_physical_width(runtime->format) *
						runtime->channels) / 8;
	bps = salign * runtime->rate;
	if (bps <= 0 || salign <= 0)
		return -EINVAL;

	dpcm->buf_pos = 0;
	dpcm->pcm_buffer_size = frames_to_bytes(runtime, runtime->buffer_size);
	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
		/* clear capture buffer */
		dpcm->silent_size = dpcm->pcm_buffer_size;
		snd_pcm_format_set_silence(runtime->format, runtime->dma_area,
					   runtime->buffer_size * runtime->channels);
	}

	dpcm->irq_pos = 0;
	dpcm->period_update_pending = 0;
	dpcm->pcm_bps = bps;
	dpcm->pcm_salign = salign;
	dpcm->pcm_period_size = frames_to_bytes(runtime, runtime->period_size);

	mutex_lock(&dpcm->loopback->cable_lock);
	if (!(cable->valid & ~(1 << substream->stream)) ||
            (get_setup(dpcm)->notify &&
	     substream->stream == SNDRV_PCM_STREAM_PLAYBACK))
		params_change(substream);
	cable->valid |= 1 << substream->stream;
	mutex_unlock(&dpcm->loopback->cable_lock);

	return 0;
}