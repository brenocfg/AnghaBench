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
struct TYPE_4__ {struct mmp_audio_platdata* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mmp_audio_platdata {int /*<<< orphan*/  period_max_capture; int /*<<< orphan*/  buffer_max_capture; int /*<<< orphan*/  period_max_playback; int /*<<< orphan*/  buffer_max_playback; } ;
struct TYPE_3__ {int /*<<< orphan*/  period_bytes_max; int /*<<< orphan*/  buffer_bytes_max; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int devm_snd_soc_register_component (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* mmp_pcm_hardware ; 
 int /*<<< orphan*/  mmp_soc_component ; 

__attribute__((used)) static int mmp_pcm_probe(struct platform_device *pdev)
{
	struct mmp_audio_platdata *pdata = pdev->dev.platform_data;

	if (pdata) {
		mmp_pcm_hardware[SNDRV_PCM_STREAM_PLAYBACK].buffer_bytes_max =
						pdata->buffer_max_playback;
		mmp_pcm_hardware[SNDRV_PCM_STREAM_PLAYBACK].period_bytes_max =
						pdata->period_max_playback;
		mmp_pcm_hardware[SNDRV_PCM_STREAM_CAPTURE].buffer_bytes_max =
						pdata->buffer_max_capture;
		mmp_pcm_hardware[SNDRV_PCM_STREAM_CAPTURE].period_bytes_max =
						pdata->period_max_capture;
	}
	return devm_snd_soc_register_component(&pdev->dev, &mmp_soc_component,
					       NULL, 0);
}