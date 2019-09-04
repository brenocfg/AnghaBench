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
struct snd_soc_pcm_runtime {TYPE_4__* codec_dai; TYPE_6__* cpu_dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_8__ {int channels_min; int channels_max; } ;
struct TYPE_12__ {int channels_min; int channels_max; } ;
struct TYPE_14__ {TYPE_1__ capture; TYPE_5__ playback; } ;
struct TYPE_13__ {TYPE_7__* driver; } ;
struct TYPE_11__ {TYPE_3__* driver; } ;
struct TYPE_9__ {int channels_max; } ;
struct TYPE_10__ {TYPE_2__ capture; } ;

/* Variables and functions */

__attribute__((used)) static void audioinjector_octo_shutdown(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	rtd->cpu_dai->driver->playback.channels_min = 2;
	rtd->cpu_dai->driver->playback.channels_max = 2;
	rtd->cpu_dai->driver->capture.channels_min = 2;
	rtd->cpu_dai->driver->capture.channels_max = 2;
	rtd->codec_dai->driver->capture.channels_max = 6;
}