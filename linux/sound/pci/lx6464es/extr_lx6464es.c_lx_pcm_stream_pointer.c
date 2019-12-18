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
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
struct lx_stream {int frame_pos; } ;
struct lx6464es {TYPE_2__* card; int /*<<< orphan*/  lock; struct lx_stream playback_stream; struct lx_stream capture_stream; } ;
typedef  int snd_pcm_uframes_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int period_size; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct lx6464es* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t lx_pcm_stream_pointer(struct snd_pcm_substream
					       *substream)
{
	struct lx6464es *chip = snd_pcm_substream_chip(substream);
	snd_pcm_uframes_t pos;
	int is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);

	struct lx_stream *lx_stream = is_capture ? &chip->capture_stream :
		&chip->playback_stream;

	dev_dbg(chip->card->dev, "->lx_pcm_stream_pointer\n");

	mutex_lock(&chip->lock);
	pos = lx_stream->frame_pos * substream->runtime->period_size;
	mutex_unlock(&chip->lock);

	dev_dbg(chip->card->dev, "stream_pointer at %ld\n", pos);
	return pos;
}