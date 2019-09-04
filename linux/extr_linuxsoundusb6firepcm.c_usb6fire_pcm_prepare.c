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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ rate; } ;
struct pcm_substream {scalar_t__ period_off; scalar_t__ dma_off; } ;
struct pcm_runtime {scalar_t__ stream_state; size_t rate; int /*<<< orphan*/  stream_mutex; TYPE_2__* chip; scalar_t__ panic; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPIPE ; 
 scalar_t__ STREAM_DISABLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__* rates ; 
 struct pcm_runtime* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 struct pcm_substream* usb6fire_pcm_get_substream (struct snd_pcm_substream*) ; 
 int usb6fire_pcm_set_rate (struct pcm_runtime*) ; 
 int usb6fire_pcm_stream_start (struct pcm_runtime*) ; 

__attribute__((used)) static int usb6fire_pcm_prepare(struct snd_pcm_substream *alsa_sub)
{
	struct pcm_runtime *rt = snd_pcm_substream_chip(alsa_sub);
	struct pcm_substream *sub = usb6fire_pcm_get_substream(alsa_sub);
	struct snd_pcm_runtime *alsa_rt = alsa_sub->runtime;
	int ret;

	if (rt->panic)
		return -EPIPE;
	if (!sub)
		return -ENODEV;

	mutex_lock(&rt->stream_mutex);
	sub->dma_off = 0;
	sub->period_off = 0;

	if (rt->stream_state == STREAM_DISABLED) {
		for (rt->rate = 0; rt->rate < ARRAY_SIZE(rates); rt->rate++)
			if (alsa_rt->rate == rates[rt->rate])
				break;
		if (rt->rate == ARRAY_SIZE(rates)) {
			mutex_unlock(&rt->stream_mutex);
			dev_err(&rt->chip->dev->dev,
				"invalid rate %d in prepare.\n",
				alsa_rt->rate);
			return -EINVAL;
		}

		ret = usb6fire_pcm_set_rate(rt);
		if (ret) {
			mutex_unlock(&rt->stream_mutex);
			return ret;
		}
		ret = usb6fire_pcm_stream_start(rt);
		if (ret) {
			mutex_unlock(&rt->stream_mutex);
			dev_err(&rt->chip->dev->dev,
				"could not start pcm stream.\n");
			return ret;
		}
	}
	mutex_unlock(&rt->stream_mutex);
	return 0;
}