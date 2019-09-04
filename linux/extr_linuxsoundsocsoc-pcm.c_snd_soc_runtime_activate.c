#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int num_codecs; TYPE_3__** codec_dais; int /*<<< orphan*/  pcm_mutex; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {TYPE_1__* component; int /*<<< orphan*/  active; int /*<<< orphan*/  capture_active; int /*<<< orphan*/  playback_active; } ;
struct TYPE_6__ {TYPE_2__* component; int /*<<< orphan*/  active; int /*<<< orphan*/  capture_active; int /*<<< orphan*/  playback_active; } ;
struct TYPE_5__ {int /*<<< orphan*/  active; } ;
struct TYPE_4__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void snd_soc_runtime_activate(struct snd_soc_pcm_runtime *rtd, int stream)
{
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	int i;

	lockdep_assert_held(&rtd->pcm_mutex);

	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		cpu_dai->playback_active++;
		for (i = 0; i < rtd->num_codecs; i++)
			rtd->codec_dais[i]->playback_active++;
	} else {
		cpu_dai->capture_active++;
		for (i = 0; i < rtd->num_codecs; i++)
			rtd->codec_dais[i]->capture_active++;
	}

	cpu_dai->active++;
	cpu_dai->component->active++;
	for (i = 0; i < rtd->num_codecs; i++) {
		rtd->codec_dais[i]->active++;
		rtd->codec_dais[i]->component->active++;
	}
}