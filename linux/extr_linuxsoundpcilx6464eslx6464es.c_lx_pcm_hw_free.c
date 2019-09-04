#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; } ;
struct TYPE_6__ {int /*<<< orphan*/ * stream; } ;
struct TYPE_5__ {int /*<<< orphan*/ * stream; } ;
struct lx6464es {int /*<<< orphan*/  setup_mutex; TYPE_3__ playback_stream; TYPE_2__ capture_stream; scalar_t__* hardware_running; TYPE_1__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int lx_hardware_close (struct lx6464es*,struct snd_pcm_substream*) ; 
 int lx_hardware_stop (struct lx6464es*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct lx6464es* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int lx_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct lx6464es *chip = snd_pcm_substream_chip(substream);
	int err = 0;
	int is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);

	dev_dbg(chip->card->dev, "->lx_pcm_hw_free\n");
	mutex_lock(&chip->setup_mutex);

	if (chip->hardware_running[is_capture]) {
		err = lx_hardware_stop(chip, substream);
		if (err < 0) {
			dev_err(chip->card->dev, "failed to stop hardware. "
				   "Error code %d\n", err);
			goto exit;
		}

		err = lx_hardware_close(chip, substream);
		if (err < 0) {
			dev_err(chip->card->dev, "failed to close hardware. "
				   "Error code %d\n", err);
			goto exit;
		}

		chip->hardware_running[is_capture] = 0;
	}

	err = snd_pcm_lib_free_pages(substream);

	if (is_capture)
		chip->capture_stream.stream = NULL;
	else
		chip->playback_stream.stream = NULL;

exit:
	mutex_unlock(&chip->setup_mutex);
	return err;
}