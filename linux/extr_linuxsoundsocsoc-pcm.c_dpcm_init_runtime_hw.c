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
struct snd_soc_pcm_stream {int formats; int /*<<< orphan*/  rates; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rate_min; } ;
struct TYPE_2__ {int formats; int /*<<< orphan*/  rates; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rate_min; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;

/* Variables and functions */

__attribute__((used)) static void dpcm_init_runtime_hw(struct snd_pcm_runtime *runtime,
				 struct snd_soc_pcm_stream *stream)
{
	runtime->hw.rate_min = stream->rate_min;
	runtime->hw.rate_max = stream->rate_max;
	runtime->hw.channels_min = stream->channels_min;
	runtime->hw.channels_max = stream->channels_max;
	if (runtime->hw.formats)
		runtime->hw.formats &= stream->formats;
	else
		runtime->hw.formats = stream->formats;
	runtime->hw.rates = stream->rates;
}