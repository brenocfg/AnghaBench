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
typedef  scalar_t__ u_int32_t ;
struct snd_pcxhr {TYPE_1__* mgr; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int period_size; struct pcxhr_stream* private_data; } ;
struct pcxhr_stream {int timer_buf_periods; scalar_t__ timer_period_frag; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_pcxhr* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t pcxhr_stream_pointer(struct snd_pcm_substream *subs)
{
	u_int32_t timer_period_frag;
	int timer_buf_periods;
	struct snd_pcxhr *chip = snd_pcm_substream_chip(subs);
	struct snd_pcm_runtime *runtime = subs->runtime;
	struct pcxhr_stream *stream  = runtime->private_data;

	mutex_lock(&chip->mgr->lock);

	/* get the period fragment and the nb of periods in the buffer */
	timer_period_frag = stream->timer_period_frag;
	timer_buf_periods = stream->timer_buf_periods;

	mutex_unlock(&chip->mgr->lock);

	return (snd_pcm_uframes_t)((timer_buf_periods * runtime->period_size) +
				   timer_period_frag);
}