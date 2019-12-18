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
struct snd_pcm_substream {int stream; TYPE_1__* runtime; int /*<<< orphan*/  name; } ;
struct hdac_stream {int /*<<< orphan*/  stream_tag; } ;
struct TYPE_2__ {struct hdac_stream* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int hda_dsp_stream_put (struct snd_sof_dev*,int,int /*<<< orphan*/ ) ; 

int hda_dsp_pcm_close(struct snd_sof_dev *sdev,
		      struct snd_pcm_substream *substream)
{
	struct hdac_stream *hstream = substream->runtime->private_data;
	int direction = substream->stream;
	int ret;

	ret = hda_dsp_stream_put(sdev, direction, hstream->stream_tag);

	if (ret) {
		dev_dbg(sdev->dev, "stream %s not opened!\n", substream->name);
		return -ENODEV;
	}

	/* unbinding pcm substream to hda stream */
	substream->runtime->private_data = NULL;
	return 0;
}