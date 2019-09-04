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
struct lola_stream {int dummy; } ;
struct lola_pcm {int dummy; } ;
struct lola {int /*<<< orphan*/  open_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  lola_cleanup_slave_streams (struct lola_pcm*,struct lola_stream*) ; 
 struct lola_pcm* lola_get_pcm (struct snd_pcm_substream*) ; 
 struct lola_stream* lola_get_stream (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  lola_stream_reset (struct lola*,struct lola_stream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct lola* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int lola_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct lola *chip = snd_pcm_substream_chip(substream);
	struct lola_pcm *pcm = lola_get_pcm(substream);
	struct lola_stream *str = lola_get_stream(substream);

	mutex_lock(&chip->open_mutex);
	lola_stream_reset(chip, str);
	lola_cleanup_slave_streams(pcm, str);
	mutex_unlock(&chip->open_mutex);
	return snd_pcm_lib_free_pages(substream);
}