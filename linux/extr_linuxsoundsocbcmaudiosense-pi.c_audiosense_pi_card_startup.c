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
struct TYPE_2__ {int channels_max; int /*<<< orphan*/  formats; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S16_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  audiosense_constraints_ch ; 
 int /*<<< orphan*/  audiosense_constraints_rates ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_msbits (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int audiosense_pi_card_startup(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;

	/*
	 * Set codec to 48Khz Sampling, Stereo I/O and 16 bit audio
	 */
	runtime->hw.channels_max = 2;
	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				   &audiosense_constraints_ch);

	runtime->hw.formats = SNDRV_PCM_FMTBIT_S16_LE;
	snd_pcm_hw_constraint_msbits(runtime, 0, 16, 16);


	snd_pcm_hw_constraint_list(substream->runtime, 0,
				   SNDRV_PCM_HW_PARAM_RATE,
				   &audiosense_constraints_rates);
	return 0;
}