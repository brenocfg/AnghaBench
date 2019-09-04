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
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  rate; } ;
struct lola_stream {scalar_t__ index; int opened; unsigned int bufsize; unsigned int period_bytes; unsigned int format_verb; struct lola_stream* master; } ;
struct lola_pcm {scalar_t__ num_streams; } ;
struct lola {int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  open_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  lola_cleanup_slave_streams (struct lola_pcm*,struct lola_stream*) ; 
 unsigned int lola_get_format_verb (struct snd_pcm_substream*) ; 
 struct lola_pcm* lola_get_pcm (struct snd_pcm_substream*) ; 
 struct lola_stream* lola_get_stream (struct snd_pcm_substream*) ; 
 int lola_set_sample_rate (struct lola*,int /*<<< orphan*/ ) ; 
 int lola_set_stream_config (struct lola*,struct lola_stream*,int) ; 
 int lola_setup_controller (struct lola*,struct lola_pcm*,struct lola_stream*) ; 
 int lola_setup_periods (struct lola*,struct lola_pcm*,struct snd_pcm_substream*,struct lola_stream*) ; 
 int /*<<< orphan*/  lola_stream_reset (struct lola*,struct lola_stream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct lola* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int lola_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct lola *chip = snd_pcm_substream_chip(substream);
	struct lola_pcm *pcm = lola_get_pcm(substream);
	struct lola_stream *str = lola_get_stream(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int bufsize, period_bytes, format_verb;
	int i, err;

	mutex_lock(&chip->open_mutex);
	lola_stream_reset(chip, str);
	lola_cleanup_slave_streams(pcm, str);
	if (str->index + runtime->channels > pcm->num_streams) {
		mutex_unlock(&chip->open_mutex);
		return -EINVAL;
	}
	for (i = 1; i < runtime->channels; i++) {
		str[i].master = str;
		str[i].opened = 1;
	}
	mutex_unlock(&chip->open_mutex);

	bufsize = snd_pcm_lib_buffer_bytes(substream);
	period_bytes = snd_pcm_lib_period_bytes(substream);
	format_verb = lola_get_format_verb(substream);

	str->bufsize = bufsize;
	str->period_bytes = period_bytes;
	str->format_verb = format_verb;

	err = lola_setup_periods(chip, pcm, substream, str);
	if (err < 0)
		return err;

	err = lola_set_sample_rate(chip, runtime->rate);
	if (err < 0)
		return err;
	chip->sample_rate = runtime->rate;	/* sample rate gets locked */

	err = lola_set_stream_config(chip, str, runtime->channels);
	if (err < 0)
		return err;

	err = lola_setup_controller(chip, pcm, str);
	if (err < 0) {
		lola_stream_reset(chip, str);
		return err;
	}

	return 0;
}