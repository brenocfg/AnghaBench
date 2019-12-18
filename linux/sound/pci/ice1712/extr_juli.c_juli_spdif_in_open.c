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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {int rate_min; int rate_max; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct snd_ice1712 {int /*<<< orphan*/  (* is_spdif_master ) (struct snd_ice1712*) ;struct juli_spec* spec; } ;
struct juli_spec {int /*<<< orphan*/  ak4114; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int snd_ak4114_external_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_ice1712*) ; 

__attribute__((used)) static void juli_spdif_in_open(struct snd_ice1712 *ice,
				struct snd_pcm_substream *substream)
{
	struct juli_spec *spec = ice->spec;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int rate;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK ||
			!ice->is_spdif_master(ice))
		return;
	rate = snd_ak4114_external_rate(spec->ak4114);
	if (rate >= runtime->hw.rate_min && rate <= runtime->hw.rate_max) {
		runtime->hw.rate_min = rate;
		runtime->hw.rate_max = rate;
	}
}