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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  rate; } ;
struct pcm_substream {scalar_t__ period_off; scalar_t__ dma_off; } ;
struct pcm_runtime {scalar_t__ stream_state; int /*<<< orphan*/  stream_mutex; scalar_t__ panic; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPIPE ; 
 scalar_t__ STREAM_DISABLED ; 
 struct pcm_substream* hiface_pcm_get_substream (struct snd_pcm_substream*) ; 
 int hiface_pcm_set_rate (struct pcm_runtime*,int /*<<< orphan*/ ) ; 
 int hiface_pcm_stream_start (struct pcm_runtime*) ; 
 int /*<<< orphan*/  hiface_pcm_stream_stop (struct pcm_runtime*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pcm_runtime* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int hiface_pcm_prepare(struct snd_pcm_substream *alsa_sub)
{
	struct pcm_runtime *rt = snd_pcm_substream_chip(alsa_sub);
	struct pcm_substream *sub = hiface_pcm_get_substream(alsa_sub);
	struct snd_pcm_runtime *alsa_rt = alsa_sub->runtime;
	int ret;

	if (rt->panic)
		return -EPIPE;
	if (!sub)
		return -ENODEV;

	mutex_lock(&rt->stream_mutex);

	hiface_pcm_stream_stop(rt);

	sub->dma_off = 0;
	sub->period_off = 0;

	if (rt->stream_state == STREAM_DISABLED) {

		ret = hiface_pcm_set_rate(rt, alsa_rt->rate);
		if (ret) {
			mutex_unlock(&rt->stream_mutex);
			return ret;
		}
		ret = hiface_pcm_stream_start(rt);
		if (ret) {
			mutex_unlock(&rt->stream_mutex);
			return ret;
		}
	}
	mutex_unlock(&rt->stream_mutex);
	return 0;
}