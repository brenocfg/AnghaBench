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
struct snd_pcm {TYPE_1__* streams; } ;
struct TYPE_4__ {int device; int subdevice; } ;
struct snd_kcontrol {TYPE_2__ id; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;
struct loopback_setup {int notify; int rate; int channels; TYPE_2__ channels_id; TYPE_2__ rate_id; TYPE_2__ format_id; TYPE_2__ active_id; int /*<<< orphan*/  format; int /*<<< orphan*/  rate_shift; } ;
struct loopback {struct loopback_setup** setup; struct snd_pcm** pcm; struct snd_card* card; } ;
struct TYPE_3__ {int substream_count; } ;

/* Variables and functions */
#define  ACTIVE_IDX 131 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
#define  CHANNELS_IDX 130 
 int ENOMEM ; 
#define  FORMAT_IDX 129 
 int /*<<< orphan*/  NO_PITCH ; 
#define  RATE_IDX 128 
 int /*<<< orphan*/  SNDRV_PCM_FORMAT_S16_LE ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/ * loopback_controls ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct loopback*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int loopback_mixer_new(struct loopback *loopback, int notify)
{
	struct snd_card *card = loopback->card;
	struct snd_pcm *pcm;
	struct snd_kcontrol *kctl;
	struct loopback_setup *setup;
	int err, dev, substr, substr_count, idx;

	strcpy(card->mixername, "Loopback Mixer");
	for (dev = 0; dev < 2; dev++) {
		pcm = loopback->pcm[dev];
		substr_count =
		    pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream_count;
		for (substr = 0; substr < substr_count; substr++) {
			setup = &loopback->setup[substr][dev];
			setup->notify = notify;
			setup->rate_shift = NO_PITCH;
			setup->format = SNDRV_PCM_FORMAT_S16_LE;
			setup->rate = 48000;
			setup->channels = 2;
			for (idx = 0; idx < ARRAY_SIZE(loopback_controls);
									idx++) {
				kctl = snd_ctl_new1(&loopback_controls[idx],
						    loopback);
				if (!kctl)
					return -ENOMEM;
				kctl->id.device = dev;
				kctl->id.subdevice = substr;
				switch (idx) {
				case ACTIVE_IDX:
					setup->active_id = kctl->id;
					break;
				case FORMAT_IDX:
					setup->format_id = kctl->id;
					break;
				case RATE_IDX:
					setup->rate_id = kctl->id;
					break;
				case CHANNELS_IDX:
					setup->channels_id = kctl->id;
					break;
				default:
					break;
				}
				err = snd_ctl_add(card, kctl);
				if (err < 0)
					return err;
			}
		}
	}
	return 0;
}