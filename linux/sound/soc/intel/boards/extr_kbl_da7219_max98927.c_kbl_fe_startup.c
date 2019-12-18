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
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  formats; int /*<<< orphan*/  channels_max; } ;
struct snd_pcm_runtime {TYPE_2__ hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUAL_CHANNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S16_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S24_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  constraints_channels ; 
 int /*<<< orphan*/  constraints_rates ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_msbits (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int kbl_fe_startup(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *soc_rt = substream->private_data;

	/*
	 * On this platform for PCM device we support,
	 * 48Khz
	 * stereo
	 */

	runtime->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
					   &constraints_channels);
	/*
	 * Setup S24_LE (32 bit container and 24 bit valid data) for
	 * kblda7219m98373 & kblmax98373. For kblda7219m98927 &
	 * kblmax98927 keeping it as 16/16 due to topology FW dependency.
	 */
	if (!strcmp(soc_rt->card->name, "kblda7219m98373") ||
		!strcmp(soc_rt->card->name, "kblmax98373")) {
		runtime->hw.formats = SNDRV_PCM_FMTBIT_S24_LE;
		snd_pcm_hw_constraint_msbits(runtime, 0, 32, 24);

	} else {
		runtime->hw.formats = SNDRV_PCM_FMTBIT_S16_LE;
		snd_pcm_hw_constraint_msbits(runtime, 0, 16, 16);
	}

	snd_pcm_hw_constraint_list(runtime, 0,
				SNDRV_PCM_HW_PARAM_RATE, &constraints_rates);

	return 0;
}