#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;

/* Variables and functions */
 int SNDRV_PCM_FMTBIT_S16_LE ; 
 int SNDRV_PCM_FMTBIT_S24_LE ; 
 int SNDRV_PCM_FMTBIT_S32_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  constraints_rates ; 
 int snd_pcm_hw_constraint_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snd_pcm_hw_constraint_mask64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_pcm_hw_constraint_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pisnd_startup(struct snd_pcm_substream *substream)
{
	int err = snd_pcm_hw_constraint_list(
		substream->runtime,
		0,
		SNDRV_PCM_HW_PARAM_RATE,
		&constraints_rates
		);

	if (err < 0)
		return err;

	err = snd_pcm_hw_constraint_single(
		substream->runtime,
		SNDRV_PCM_HW_PARAM_CHANNELS,
		2
		);

	if (err < 0)
		return err;

	err = snd_pcm_hw_constraint_mask64(
		substream->runtime,
		SNDRV_PCM_HW_PARAM_FORMAT,
		SNDRV_PCM_FMTBIT_S16_LE |
		SNDRV_PCM_FMTBIT_S24_LE |
		SNDRV_PCM_FMTBIT_S32_LE
		);

	if (err < 0)
		return err;

	return 0;
}