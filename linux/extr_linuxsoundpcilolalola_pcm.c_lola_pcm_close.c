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
struct snd_pcm_substream {int dummy; } ;
struct lola_stream {scalar_t__ opened; struct snd_pcm_substream* substream; } ;
struct lola {scalar_t__ ref_count_rate; int /*<<< orphan*/  open_mutex; scalar_t__ sample_rate; } ;

/* Variables and functions */
 struct lola_stream* lola_get_stream (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct lola* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int lola_pcm_close(struct snd_pcm_substream *substream)
{
	struct lola *chip = snd_pcm_substream_chip(substream);
	struct lola_stream *str = lola_get_stream(substream);

	mutex_lock(&chip->open_mutex);
	if (str->substream == substream) {
		str->substream = NULL;
		str->opened = 0;
	}
	if (--chip->ref_count_rate == 0) {
		/* release sample rate */
		chip->sample_rate = 0;
	}
	mutex_unlock(&chip->open_mutex);
	return 0;
}