#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_3__ {int rates; int rate_max; int /*<<< orphan*/  formats; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct cmipci {int chip_version; int /*<<< orphan*/  dig_status; int /*<<< orphan*/  dig_pcm_status; scalar_t__ can_96k; scalar_t__ can_ac3_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_OPEN_SPDIF_PLAYBACK ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S32_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int SNDRV_PCM_RATE_88200 ; 
 int SNDRV_PCM_RATE_96000 ; 
 int open_device_check (struct cmipci*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 TYPE_1__ snd_cmipci_playback_iec958_subframe ; 
 TYPE_1__ snd_cmipci_playback_spdif ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_msbits (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 struct cmipci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cmipci_playback_spdif_open(struct snd_pcm_substream *substream)
{
	struct cmipci *cm = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	if ((err = open_device_check(cm, CM_OPEN_SPDIF_PLAYBACK, substream)) < 0) /* use channel A */
		return err;
	if (cm->can_ac3_hw) {
		runtime->hw = snd_cmipci_playback_spdif;
		if (cm->chip_version >= 37) {
			runtime->hw.formats |= SNDRV_PCM_FMTBIT_S32_LE;
			snd_pcm_hw_constraint_msbits(runtime, 0, 32, 24);
		}
		if (cm->can_96k) {
			runtime->hw.rates |= SNDRV_PCM_RATE_88200 |
					     SNDRV_PCM_RATE_96000;
			runtime->hw.rate_max = 96000;
		}
	} else {
		runtime->hw = snd_cmipci_playback_iec958_subframe;
	}
	snd_pcm_hw_constraint_minmax(runtime, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 0, 0x40000);
	cm->dig_pcm_status = cm->dig_status;
	return 0;
}