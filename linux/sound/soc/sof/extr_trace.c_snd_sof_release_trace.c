#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_sof_dev {int dtrace_is_enabled; int dtrace_draining; int /*<<< orphan*/  trace_sleep; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_TRIGGER_STOP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_sof_dma_trace_release (struct snd_sof_dev*) ; 
 int snd_sof_dma_trace_trigger (struct snd_sof_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void snd_sof_release_trace(struct snd_sof_dev *sdev)
{
	int ret;

	if (!sdev->dtrace_is_enabled)
		return;

	ret = snd_sof_dma_trace_trigger(sdev, SNDRV_PCM_TRIGGER_STOP);
	if (ret < 0)
		dev_err(sdev->dev,
			"error: snd_sof_dma_trace_trigger: stop: %d\n", ret);

	ret = snd_sof_dma_trace_release(sdev);
	if (ret < 0)
		dev_err(sdev->dev,
			"error: fail in snd_sof_dma_trace_release %d\n", ret);

	sdev->dtrace_is_enabled = false;
	sdev->dtrace_draining = true;
	wake_up(&sdev->trace_sleep);
}