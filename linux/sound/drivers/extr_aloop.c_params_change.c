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
struct snd_pcm_runtime {int /*<<< orphan*/  channels; int /*<<< orphan*/  rate; int /*<<< orphan*/  format; struct loopback_pcm* private_data; } ;
struct loopback_pcm {struct loopback_cable* cable; } ;
struct TYPE_2__ {int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rate_min; int /*<<< orphan*/  formats; } ;
struct loopback_cable {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcm_format_to_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void params_change(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct loopback_pcm *dpcm = runtime->private_data;
	struct loopback_cable *cable = dpcm->cable;

	cable->hw.formats = pcm_format_to_bits(runtime->format);
	cable->hw.rate_min = runtime->rate;
	cable->hw.rate_max = runtime->rate;
	cable->hw.channels_min = runtime->channels;
	cable->hw.channels_max = runtime->channels;
}