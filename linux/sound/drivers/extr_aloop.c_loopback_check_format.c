#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_runtime {scalar_t__ format; scalar_t__ rate; scalar_t__ channels; } ;
struct snd_card {int dummy; } ;
struct loopback_setup {scalar_t__ format; scalar_t__ rate; scalar_t__ channels; int /*<<< orphan*/  channels_id; int /*<<< orphan*/  rate_id; int /*<<< orphan*/  format_id; } ;
struct loopback_cable {scalar_t__ valid; TYPE_3__** streams; } ;
struct TYPE_6__ {TYPE_1__* loopback; TYPE_2__* substream; } ;
struct TYPE_5__ {struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {struct snd_card* card; } ;

/* Variables and functions */
 scalar_t__ CABLE_VALID_BOTH ; 
 int EIO ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  SNDRV_PCM_STATE_DRAINING ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 struct loopback_setup* get_setup (TYPE_3__*) ; 
 int /*<<< orphan*/  snd_ctl_notify (struct snd_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_stop (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int loopback_check_format(struct loopback_cable *cable, int stream)
{
	struct snd_pcm_runtime *runtime, *cruntime;
	struct loopback_setup *setup;
	struct snd_card *card;
	int check;

	if (cable->valid != CABLE_VALID_BOTH) {
		if (stream == SNDRV_PCM_STREAM_PLAYBACK)
			goto __notify;
		return 0;
	}
	runtime = cable->streams[SNDRV_PCM_STREAM_PLAYBACK]->
							substream->runtime;
	cruntime = cable->streams[SNDRV_PCM_STREAM_CAPTURE]->
							substream->runtime;
	check = runtime->format != cruntime->format ||
		runtime->rate != cruntime->rate ||
		runtime->channels != cruntime->channels;
	if (!check)
		return 0;
	if (stream == SNDRV_PCM_STREAM_CAPTURE) {
		return -EIO;
	} else {
		snd_pcm_stop(cable->streams[SNDRV_PCM_STREAM_CAPTURE]->
					substream, SNDRV_PCM_STATE_DRAINING);
	      __notify:
		runtime = cable->streams[SNDRV_PCM_STREAM_PLAYBACK]->
							substream->runtime;
		setup = get_setup(cable->streams[SNDRV_PCM_STREAM_PLAYBACK]);
		card = cable->streams[SNDRV_PCM_STREAM_PLAYBACK]->loopback->card;
		if (setup->format != runtime->format) {
			snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE,
							&setup->format_id);
			setup->format = runtime->format;
		}
		if (setup->rate != runtime->rate) {
			snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE,
							&setup->rate_id);
			setup->rate = runtime->rate;
		}
		if (setup->channels != runtime->channels) {
			snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE,
							&setup->channels_id);
			setup->channels = runtime->channels;
		}
	}
	return 0;
}