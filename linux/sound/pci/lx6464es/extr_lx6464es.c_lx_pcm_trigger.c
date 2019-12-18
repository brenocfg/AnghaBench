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
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct lx_stream {int dummy; } ;
struct lx6464es {TYPE_1__* card; struct lx_stream playback_stream; struct lx_stream capture_stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int lx_pcm_trigger_dispatch (struct lx6464es*,struct lx_stream*,int) ; 
 struct lx6464es* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int lx_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct lx6464es *chip = snd_pcm_substream_chip(substream);
	const int is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);
	struct lx_stream *stream = is_capture ? &chip->capture_stream :
		&chip->playback_stream;

	dev_dbg(chip->card->dev, "->lx_pcm_trigger\n");

	return lx_pcm_trigger_dispatch(chip, stream, cmd);
}