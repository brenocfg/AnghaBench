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
struct sof_intel_hda_dev {int /*<<< orphan*/  dtrace_stream; } ;
struct snd_sof_dev {TYPE_1__* pdata; } ;
struct TYPE_2__ {struct sof_intel_hda_dev* hw_pdata; } ;

/* Variables and functions */
 int hda_dsp_stream_trigger (struct snd_sof_dev*,int /*<<< orphan*/ ,int) ; 

int hda_dsp_trace_trigger(struct snd_sof_dev *sdev, int cmd)
{
	struct sof_intel_hda_dev *hda = sdev->pdata->hw_pdata;

	return hda_dsp_stream_trigger(sdev, hda->dtrace_stream, cmd);
}