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
struct snd_pcxhr {int** digital_playback_active; int* aes_bits; int* analog_playback_active; int analog_capture_active; TYPE_1__* mgr; int /*<<< orphan*/ * analog_capture_volume; void** digital_capture_volume; scalar_t__ nb_streams_capt; int /*<<< orphan*/ * analog_playback_volume; void*** digital_playback_volume; scalar_t__ nb_streams_play; } ;
struct TYPE_2__ {scalar_t__ is_hr_stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  HR222_LINE_CAPTURE_ZERO_LEVEL ; 
 int /*<<< orphan*/  HR222_LINE_PLAYBACK_ZERO_LEVEL ; 
 int IEC958_AES0_PROFESSIONAL ; 
 int IEC958_AES0_PRO_FS_48000 ; 
 void* PCXHR_DIGITAL_ZERO_LEVEL ; 
 int /*<<< orphan*/  PCXHR_LINE_CAPTURE_ZERO_LEVEL ; 
 int /*<<< orphan*/  PCXHR_LINE_PLAYBACK_ZERO_LEVEL ; 
 int PCXHR_PLAYBACK_STREAMS ; 
 int /*<<< orphan*/  hr222_update_analog_audio_level (struct snd_pcxhr*,int,int) ; 
 int /*<<< orphan*/  pcxhr_update_analog_audio_level (struct snd_pcxhr*,int,int) ; 

__attribute__((used)) static void pcxhr_init_audio_levels(struct snd_pcxhr *chip)
{
	int i;

	for (i = 0; i < 2; i++) {
		if (chip->nb_streams_play) {
			int j;
			/* at boot time the digital volumes are unmuted 0dB */
			for (j = 0; j < PCXHR_PLAYBACK_STREAMS; j++) {
				chip->digital_playback_active[j][i] = 1;
				chip->digital_playback_volume[j][i] =
					PCXHR_DIGITAL_ZERO_LEVEL;
			}
			/* after boot, only two bits are set on the uer
			 * interface
			 */
			chip->aes_bits[0] = (IEC958_AES0_PROFESSIONAL |
					     IEC958_AES0_PRO_FS_48000);
#ifdef CONFIG_SND_DEBUG
			/* analog volumes for playback
			 * (is LEVEL_MIN after boot)
			 */
			chip->analog_playback_active[i] = 1;
			if (chip->mgr->is_hr_stereo)
				chip->analog_playback_volume[i] =
					HR222_LINE_PLAYBACK_ZERO_LEVEL;
			else {
				chip->analog_playback_volume[i] =
					PCXHR_LINE_PLAYBACK_ZERO_LEVEL;
				pcxhr_update_analog_audio_level(chip, 0, i);
			}
#endif
			/* stereo cards need to be initialised after boot */
			if (chip->mgr->is_hr_stereo)
				hr222_update_analog_audio_level(chip, 0, i);
		}
		if (chip->nb_streams_capt) {
			/* at boot time the digital volumes are unmuted 0dB */
			chip->digital_capture_volume[i] =
				PCXHR_DIGITAL_ZERO_LEVEL;
			chip->analog_capture_active = 1;
#ifdef CONFIG_SND_DEBUG
			/* analog volumes for playback
			 * (is LEVEL_MIN after boot)
			 */
			if (chip->mgr->is_hr_stereo)
				chip->analog_capture_volume[i] =
					HR222_LINE_CAPTURE_ZERO_LEVEL;
			else {
				chip->analog_capture_volume[i] =
					PCXHR_LINE_CAPTURE_ZERO_LEVEL;
				pcxhr_update_analog_audio_level(chip, 1, i);
			}
#endif
			/* stereo cards need to be initialised after boot */
			if (chip->mgr->is_hr_stereo)
				hr222_update_analog_audio_level(chip, 1, i);
		}
	}

	return;
}