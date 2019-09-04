#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_7__* codec_dai; TYPE_4__* cpu_dai; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_14__ {TYPE_6__* driver; } ;
struct TYPE_12__ {int channels_max; } ;
struct TYPE_13__ {TYPE_5__ capture; } ;
struct TYPE_11__ {TYPE_3__* driver; } ;
struct TYPE_9__ {int channels_min; int channels_max; } ;
struct TYPE_8__ {int channels_min; int channels_max; } ;
struct TYPE_10__ {TYPE_2__ capture; TYPE_1__ playback; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  audioinjector_octo_constraints ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int audioinjector_octo_startup(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	rtd->cpu_dai->driver->playback.channels_min = 8;
	rtd->cpu_dai->driver->playback.channels_max = 8;
	rtd->cpu_dai->driver->capture.channels_min = 8;
	rtd->cpu_dai->driver->capture.channels_max = 8;
	rtd->codec_dai->driver->capture.channels_max = 8;
	
	snd_pcm_hw_constraint_list(substream->runtime, 0,
				SNDRV_PCM_HW_PARAM_RATE,
				&audioinjector_octo_constraints);

	return 0;
}