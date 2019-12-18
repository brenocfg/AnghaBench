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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct lx6464es {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lx_pipe_release (struct lx6464es*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lx_hardware_close(struct lx6464es *chip,
			     struct snd_pcm_substream *substream)
{
	int err = 0;
	int is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);

	dev_dbg(chip->card->dev, "releasing pipe\n");
	err = lx_pipe_release(chip, 0, is_capture);
	if (err < 0) {
		dev_err(chip->card->dev, "releasing pipe failed\n");
		return err;
	}

	return err;
}