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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct snd_pcm_runtime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S16 ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S32 ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/ * drm_eld_sad (int /*<<< orphan*/  const*) ; 
 int drm_eld_sad_count (int /*<<< orphan*/  const*) ; 
 int sad_format (int /*<<< orphan*/  const*) ; 
 int sad_sample_bits_lpcm (int /*<<< orphan*/  const*) ; 
 int snd_pcm_hw_constraint_mask64 (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdac_hdmi_eld_limit_formats(struct snd_pcm_runtime *runtime,
						void *eld)
{
	u64 formats = SNDRV_PCM_FMTBIT_S16;
	int i;
	const u8 *sad, *eld_buf = eld;

	sad = drm_eld_sad(eld_buf);
	if (!sad)
		goto format_constraint;

	for (i = drm_eld_sad_count(eld_buf); i > 0; i--, sad += 3) {
		if (sad_format(sad) == 1) { /* AUDIO_CODING_TYPE_LPCM */

			/*
			 * the controller support 20 and 24 bits in 32 bit
			 * container so we set S32
			 */
			if (sad_sample_bits_lpcm(sad) & 0x6)
				formats |= SNDRV_PCM_FMTBIT_S32;
		}
	}

format_constraint:
	return snd_pcm_hw_constraint_mask64(runtime, SNDRV_PCM_HW_PARAM_FORMAT,
				formats);

}