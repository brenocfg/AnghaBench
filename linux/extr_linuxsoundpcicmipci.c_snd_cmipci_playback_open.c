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
struct TYPE_2__ {int rates; int rate_max; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct cmipci {int chip_version; int /*<<< orphan*/  dig_status; int /*<<< orphan*/  dig_pcm_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_OPEN_PLAYBACK ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int SNDRV_PCM_RATE_88200 ; 
 int SNDRV_PCM_RATE_96000 ; 
 int SNDRV_PCM_RATE_KNOT ; 
 int /*<<< orphan*/  hw_constraints_rates ; 
 int open_device_check (struct cmipci*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 TYPE_1__ snd_cmipci_playback ; 
 int snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cmipci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cmipci_playback_open(struct snd_pcm_substream *substream)
{
	struct cmipci *cm = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	if ((err = open_device_check(cm, CM_OPEN_PLAYBACK, substream)) < 0)
		return err;
	runtime->hw = snd_cmipci_playback;
	if (cm->chip_version == 68) {
		runtime->hw.rates |= SNDRV_PCM_RATE_88200 |
				     SNDRV_PCM_RATE_96000;
		runtime->hw.rate_max = 96000;
	} else if (cm->chip_version == 55) {
		err = snd_pcm_hw_constraint_list(runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE, &hw_constraints_rates);
		if (err < 0)
			return err;
		runtime->hw.rates |= SNDRV_PCM_RATE_KNOT;
		runtime->hw.rate_max = 128000;
	}
	snd_pcm_hw_constraint_minmax(runtime, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 0, 0x10000);
	cm->dig_pcm_status = cm->dig_status;
	return 0;
}