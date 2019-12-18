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
typedef  int /*<<< orphan*/  u32 ;
struct sof_intel_hda_dev {TYPE_3__* dtrace_stream; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; TYPE_2__* pdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream_tag; } ;
struct TYPE_6__ {TYPE_1__ hstream; } ;
struct TYPE_5__ {struct sof_intel_hda_dev* hw_pdata; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* hda_dsp_stream_get (struct snd_sof_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_dsp_stream_put (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hda_dsp_trace_prepare (struct snd_sof_dev*) ; 

int hda_dsp_trace_init(struct snd_sof_dev *sdev, u32 *stream_tag)
{
	struct sof_intel_hda_dev *hda = sdev->pdata->hw_pdata;
	int ret;

	hda->dtrace_stream = hda_dsp_stream_get(sdev,
						SNDRV_PCM_STREAM_CAPTURE);

	if (!hda->dtrace_stream) {
		dev_err(sdev->dev,
			"error: no available capture stream for DMA trace\n");
		return -ENODEV;
	}

	*stream_tag = hda->dtrace_stream->hstream.stream_tag;

	/*
	 * initialize capture stream, set BDL address and return corresponding
	 * stream tag which will be sent to the firmware by IPC message.
	 */
	ret = hda_dsp_trace_prepare(sdev);
	if (ret < 0) {
		dev_err(sdev->dev, "error: hdac trace init failed: %x\n", ret);
		hda_dsp_stream_put(sdev, SNDRV_PCM_STREAM_CAPTURE, *stream_tag);
		hda->dtrace_stream = NULL;
		*stream_tag = 0;
	}

	return ret;
}