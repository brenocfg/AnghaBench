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
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int stream; TYPE_1__* runtime; } ;
struct hdac_ext_stream {int /*<<< orphan*/  hstream; } ;
struct TYPE_2__ {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct hdac_ext_stream* hda_dsp_stream_get (struct snd_sof_dev*,int) ; 

int hda_dsp_pcm_open(struct snd_sof_dev *sdev,
		     struct snd_pcm_substream *substream)
{
	struct hdac_ext_stream *dsp_stream;
	int direction = substream->stream;

	dsp_stream = hda_dsp_stream_get(sdev, direction);

	if (!dsp_stream) {
		dev_err(sdev->dev, "error: no stream available\n");
		return -ENODEV;
	}

	/* binding pcm substream to hda stream */
	substream->runtime->private_data = &dsp_stream->hstream;
	return 0;
}