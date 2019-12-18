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
struct snd_pcm_sw_params {scalar_t__ tstamp_mode; scalar_t__ proto; scalar_t__ tstamp_type; scalar_t__ avail_min; scalar_t__ silence_size; scalar_t__ silence_threshold; scalar_t__ boundary; int /*<<< orphan*/  stop_threshold; int /*<<< orphan*/  start_threshold; int /*<<< orphan*/  period_step; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ boundary; scalar_t__ buffer_size; scalar_t__ tstamp_mode; scalar_t__ tstamp_type; scalar_t__ silence_threshold; scalar_t__ silence_size; int /*<<< orphan*/  stop_threshold; int /*<<< orphan*/  start_threshold; TYPE_2__* control; int /*<<< orphan*/  period_step; TYPE_1__* status; } ;
struct TYPE_4__ {scalar_t__ avail_min; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int EBADFD ; 
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ PCM_RUNTIME_CHECK (struct snd_pcm_substream*) ; 
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ SNDRV_PCM_TSTAMP_LAST ; 
 scalar_t__ SNDRV_PCM_TSTAMP_TYPE_LAST ; 
 scalar_t__ SNDRV_PROTOCOL_VERSION (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  snd_pcm_playback_silence (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_running (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 
 int snd_pcm_update_state (struct snd_pcm_substream*,struct snd_pcm_runtime*) ; 

__attribute__((used)) static int snd_pcm_sw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_sw_params *params)
{
	struct snd_pcm_runtime *runtime;
	int err;

	if (PCM_RUNTIME_CHECK(substream))
		return -ENXIO;
	runtime = substream->runtime;
	snd_pcm_stream_lock_irq(substream);
	if (runtime->status->state == SNDRV_PCM_STATE_OPEN) {
		snd_pcm_stream_unlock_irq(substream);
		return -EBADFD;
	}
	snd_pcm_stream_unlock_irq(substream);

	if (params->tstamp_mode < 0 ||
	    params->tstamp_mode > SNDRV_PCM_TSTAMP_LAST)
		return -EINVAL;
	if (params->proto >= SNDRV_PROTOCOL_VERSION(2, 0, 12) &&
	    params->tstamp_type > SNDRV_PCM_TSTAMP_TYPE_LAST)
		return -EINVAL;
	if (params->avail_min == 0)
		return -EINVAL;
	if (params->silence_size >= runtime->boundary) {
		if (params->silence_threshold != 0)
			return -EINVAL;
	} else {
		if (params->silence_size > params->silence_threshold)
			return -EINVAL;
		if (params->silence_threshold > runtime->buffer_size)
			return -EINVAL;
	}
	err = 0;
	snd_pcm_stream_lock_irq(substream);
	runtime->tstamp_mode = params->tstamp_mode;
	if (params->proto >= SNDRV_PROTOCOL_VERSION(2, 0, 12))
		runtime->tstamp_type = params->tstamp_type;
	runtime->period_step = params->period_step;
	runtime->control->avail_min = params->avail_min;
	runtime->start_threshold = params->start_threshold;
	runtime->stop_threshold = params->stop_threshold;
	runtime->silence_threshold = params->silence_threshold;
	runtime->silence_size = params->silence_size;
        params->boundary = runtime->boundary;
	if (snd_pcm_running(substream)) {
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
		    runtime->silence_size > 0)
			snd_pcm_playback_silence(substream, ULONG_MAX);
		err = snd_pcm_update_state(substream, runtime);
	}
	snd_pcm_stream_unlock_irq(substream);
	return err;
}