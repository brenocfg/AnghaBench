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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  substream_refcount; struct snd_pcm_substream* substream; } ;
struct snd_intelhad {int /*<<< orphan*/  dev; int /*<<< orphan*/  had_spinlock; TYPE_1__ stream_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  had_pcm_hardware ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_msbits (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_intelhad* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int had_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_intelhad *intelhaddata;
	struct snd_pcm_runtime *runtime;
	int retval;

	intelhaddata = snd_pcm_substream_chip(substream);
	runtime = substream->runtime;

	pm_runtime_get_sync(intelhaddata->dev);

	/* set the runtime hw parameter with local snd_pcm_hardware struct */
	runtime->hw = had_pcm_hardware;

	retval = snd_pcm_hw_constraint_integer(runtime,
			 SNDRV_PCM_HW_PARAM_PERIODS);
	if (retval < 0)
		goto error;

	/* Make sure, that the period size is always aligned
	 * 64byte boundary
	 */
	retval = snd_pcm_hw_constraint_step(substream->runtime, 0,
			SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64);
	if (retval < 0)
		goto error;

	retval = snd_pcm_hw_constraint_msbits(runtime, 0, 32, 24);
	if (retval < 0)
		goto error;

	/* expose PCM substream */
	spin_lock_irq(&intelhaddata->had_spinlock);
	intelhaddata->stream_info.substream = substream;
	intelhaddata->stream_info.substream_refcount++;
	spin_unlock_irq(&intelhaddata->had_spinlock);

	return retval;
 error:
	pm_runtime_mark_last_busy(intelhaddata->dev);
	pm_runtime_put_autosuspend(intelhaddata->dev);
	return retval;
}