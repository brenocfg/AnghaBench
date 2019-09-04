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
struct snd_timer_id {int card; int device; int subdevice; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  dev_sclass; } ;
struct snd_timer {int /*<<< orphan*/  private_free; struct snd_pcm_substream* private_data; int /*<<< orphan*/  card; int /*<<< orphan*/  hw; int /*<<< orphan*/  name; } ;
struct snd_pcm_substream {int number; int stream; struct snd_timer* timer; TYPE_1__* pcm; } ;
struct TYPE_4__ {int number; } ;
struct TYPE_3__ {int device; TYPE_2__* card; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_TIMER_CLASS_PCM ; 
 int /*<<< orphan*/  SNDRV_TIMER_SCLASS_NONE ; 
 int /*<<< orphan*/  snd_device_free (int /*<<< orphan*/ ,struct snd_timer*) ; 
 scalar_t__ snd_device_register (int /*<<< orphan*/ ,struct snd_timer*) ; 
 int /*<<< orphan*/  snd_pcm_timer ; 
 int /*<<< orphan*/  snd_pcm_timer_free ; 
 scalar_t__ snd_timer_new (TYPE_2__*,char*,struct snd_timer_id*,struct snd_timer**) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int,int,int) ; 

void snd_pcm_timer_init(struct snd_pcm_substream *substream)
{
	struct snd_timer_id tid;
	struct snd_timer *timer;

	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.dev_class = SNDRV_TIMER_CLASS_PCM;
	tid.card = substream->pcm->card->number;
	tid.device = substream->pcm->device;
	tid.subdevice = (substream->number << 1) | (substream->stream & 1);
	if (snd_timer_new(substream->pcm->card, "PCM", &tid, &timer) < 0)
		return;
	sprintf(timer->name, "PCM %s %i-%i-%i",
			substream->stream == SNDRV_PCM_STREAM_CAPTURE ?
				"capture" : "playback",
			tid.card, tid.device, tid.subdevice);
	timer->hw = snd_pcm_timer;
	if (snd_device_register(timer->card, timer) < 0) {
		snd_device_free(timer->card, timer);
		return;
	}
	timer->private_data = substream;
	timer->private_free = snd_pcm_timer_free;
	substream->timer = timer;
}