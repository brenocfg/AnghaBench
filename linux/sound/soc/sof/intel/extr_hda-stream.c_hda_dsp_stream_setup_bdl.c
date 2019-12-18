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
struct sof_intel_hda_dev {scalar_t__ no_ipc_position; } ;
struct sof_intel_dsp_bdl {int dummy; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct snd_dma_buffer {int dummy; } ;
struct TYPE_4__ {scalar_t__ area; } ;
struct hdac_stream {int period_bytes; int bufsize; int /*<<< orphan*/  no_period_wakeup; scalar_t__ frags; TYPE_2__ bdl; } ;
struct TYPE_3__ {struct sof_intel_hda_dev* hw_pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int hda_setup_bdle (struct snd_sof_dev*,struct snd_dma_buffer*,struct hdac_stream*,struct sof_intel_dsp_bdl**,int,int,int) ; 

int hda_dsp_stream_setup_bdl(struct snd_sof_dev *sdev,
			     struct snd_dma_buffer *dmab,
			     struct hdac_stream *stream)
{
	struct sof_intel_hda_dev *hda = sdev->pdata->hw_pdata;
	struct sof_intel_dsp_bdl *bdl;
	int i, offset, period_bytes, periods;
	int remain, ioc;

	period_bytes = stream->period_bytes;
	dev_dbg(sdev->dev, "period_bytes:0x%x\n", period_bytes);
	if (!period_bytes)
		period_bytes = stream->bufsize;

	periods = stream->bufsize / period_bytes;

	dev_dbg(sdev->dev, "periods:%d\n", periods);

	remain = stream->bufsize % period_bytes;
	if (remain)
		periods++;

	/* program the initial BDL entries */
	bdl = (struct sof_intel_dsp_bdl *)stream->bdl.area;
	offset = 0;
	stream->frags = 0;

	/*
	 * set IOC if don't use position IPC
	 * and period_wakeup needed.
	 */
	ioc = hda->no_ipc_position ?
	      !stream->no_period_wakeup : 0;

	for (i = 0; i < periods; i++) {
		if (i == (periods - 1) && remain)
			/* set the last small entry */
			offset = hda_setup_bdle(sdev, dmab,
						stream, &bdl, offset,
						remain, 0);
		else
			offset = hda_setup_bdle(sdev, dmab,
						stream, &bdl, offset,
						period_bytes, ioc);
	}

	return offset;
}