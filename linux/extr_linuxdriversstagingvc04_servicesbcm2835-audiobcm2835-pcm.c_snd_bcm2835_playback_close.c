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
struct snd_pcm_substream {int number; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct bcm2835_alsa_stream* private_data; } ;
struct bcm2835_chip {int opened; int /*<<< orphan*/  audio_mutex; } ;
struct bcm2835_alsa_stream {size_t idx; TYPE_1__* chip; scalar_t__ buffer_size; scalar_t__ period_size; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** alsa_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_audio_close (struct bcm2835_alsa_stream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bcm2835_chip* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_bcm2835_playback_close(struct snd_pcm_substream *substream)
{
	struct bcm2835_alsa_stream *alsa_stream;
	struct snd_pcm_runtime *runtime;
	struct bcm2835_chip *chip;

	chip = snd_pcm_substream_chip(substream);
	mutex_lock(&chip->audio_mutex);
	runtime = substream->runtime;
	alsa_stream = runtime->private_data;

	alsa_stream->period_size = 0;
	alsa_stream->buffer_size = 0;

	bcm2835_audio_close(alsa_stream);
	alsa_stream->chip->alsa_stream[alsa_stream->idx] = NULL;
	/*
	 * Do not free up alsa_stream here, it will be freed up by
	 * runtime->private_free callback we registered in *_open above
	 */

	chip->opened &= ~(1 << substream->number);

	mutex_unlock(&chip->audio_mutex);

	return 0;
}