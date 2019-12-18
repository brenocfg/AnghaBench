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
struct snd_soc_pcm_runtime {TYPE_1__* card; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  formats; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; } ;
struct snd_pcm_runtime {TYPE_2__ hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUAD_CHANNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S24_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  constraints_channels_quad ; 
 int /*<<< orphan*/  constraints_rates ; 
 int snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_msbits (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int kabylake_dmic_startup(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *soc_rt = substream->private_data;

	runtime->hw.channels_min = runtime->hw.channels_max = QUAD_CHANNEL;
	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			&constraints_channels_quad);

	/*
	 * Topology for kblda7219m98373 & kblmax98373 supports only S24_LE.
	 * The DMIC also configured for S24_LE. Forcing the DMIC format to
	 * S24_LE due to the topology FW dependency.
	 */
	if (!strcmp(soc_rt->card->name, "kblda7219m98373") ||
		!strcmp(soc_rt->card->name, "kblmax98373")) {
		runtime->hw.formats = SNDRV_PCM_FMTBIT_S24_LE;
		snd_pcm_hw_constraint_msbits(runtime, 0, 32, 24);
	}

	return snd_pcm_hw_constraint_list(substream->runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE, &constraints_rates);
}