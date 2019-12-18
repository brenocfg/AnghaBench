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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct ensoniq {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  spdif_default; int /*<<< orphan*/  spdif_stream; int /*<<< orphan*/ * playback2_substream; scalar_t__ spdif; struct snd_pcm_substream* playback1_substream; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES_MODE_PLAY1 ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  snd_ensoniq_playback1 ; 
 int /*<<< orphan*/  snd_es1370_hw_constraints_rates ; 
 int /*<<< orphan*/  snd_es1371_hw_constraints_dac_clock ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_ratdens (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct ensoniq* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ensoniq_playback1_open(struct snd_pcm_substream *substream)
{
	struct ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	ensoniq->mode |= ES_MODE_PLAY1;
	ensoniq->playback1_substream = substream;
	runtime->hw = snd_ensoniq_playback1;
	snd_pcm_set_sync(substream);
	spin_lock_irq(&ensoniq->reg_lock);
	if (ensoniq->spdif && ensoniq->playback2_substream == NULL)
		ensoniq->spdif_stream = ensoniq->spdif_default;
	spin_unlock_irq(&ensoniq->reg_lock);
#ifdef CHIP1370
	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &snd_es1370_hw_constraints_rates);
#else
	snd_pcm_hw_constraint_ratdens(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &snd_es1371_hw_constraints_dac_clock);
#endif
	return 0;
}