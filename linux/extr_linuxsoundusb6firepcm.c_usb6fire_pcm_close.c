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
struct snd_pcm_substream {int dummy; } ;
struct pcm_substream {int active; int /*<<< orphan*/  lock; int /*<<< orphan*/ * instance; } ;
struct TYPE_4__ {int /*<<< orphan*/  instance; } ;
struct TYPE_3__ {int /*<<< orphan*/  instance; } ;
struct pcm_runtime {int /*<<< orphan*/  stream_mutex; int /*<<< orphan*/  rate; TYPE_2__ capture; TYPE_1__ playback; scalar_t__ panic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rates ; 
 struct pcm_runtime* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pcm_substream* usb6fire_pcm_get_substream (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  usb6fire_pcm_stream_stop (struct pcm_runtime*) ; 

__attribute__((used)) static int usb6fire_pcm_close(struct snd_pcm_substream *alsa_sub)
{
	struct pcm_runtime *rt = snd_pcm_substream_chip(alsa_sub);
	struct pcm_substream *sub = usb6fire_pcm_get_substream(alsa_sub);
	unsigned long flags;

	if (rt->panic)
		return 0;

	mutex_lock(&rt->stream_mutex);
	if (sub) {
		/* deactivate substream */
		spin_lock_irqsave(&sub->lock, flags);
		sub->instance = NULL;
		sub->active = false;
		spin_unlock_irqrestore(&sub->lock, flags);

		/* all substreams closed? if so, stop streaming */
		if (!rt->playback.instance && !rt->capture.instance) {
			usb6fire_pcm_stream_stop(rt);
			rt->rate = ARRAY_SIZE(rates);
		}
	}
	mutex_unlock(&rt->stream_mutex);
	return 0;
}