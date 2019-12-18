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
struct sof_intel_hda_dev {struct hdac_ext_stream* dtrace_stream; } ;
struct snd_dma_buffer {int /*<<< orphan*/  bytes; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; struct snd_dma_buffer dmatb; TYPE_1__* pdata; } ;
struct hdac_stream {int /*<<< orphan*/  bufsize; scalar_t__ period_bytes; } ;
struct hdac_ext_stream {struct hdac_stream hstream; } ;
struct TYPE_2__ {struct sof_intel_hda_dev* hw_pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int hda_dsp_stream_hw_params (struct snd_sof_dev*,struct hdac_ext_stream*,struct snd_dma_buffer*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hda_dsp_trace_prepare(struct snd_sof_dev *sdev)
{
	struct sof_intel_hda_dev *hda = sdev->pdata->hw_pdata;
	struct hdac_ext_stream *stream = hda->dtrace_stream;
	struct hdac_stream *hstream = &stream->hstream;
	struct snd_dma_buffer *dmab = &sdev->dmatb;
	int ret;

	hstream->period_bytes = 0;/* initialize period_bytes */
	hstream->bufsize = sdev->dmatb.bytes;

	ret = hda_dsp_stream_hw_params(sdev, stream, dmab, NULL);
	if (ret < 0)
		dev_err(sdev->dev, "error: hdac prepare failed: %x\n", ret);

	return ret;
}