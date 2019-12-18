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
typedef  int u64 ;
struct snd_pcm_hw_rule {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {int* bits; } ;
struct snd_interval {int integer; int min; int max; } ;

/* Variables and functions */
 int SNDRV_PCM_FMTBIT_S16_LE ; 
 int SNDRV_PCM_FMTBIT_S24_3LE ; 
 int SNDRV_PCM_FMTBIT_S32_BE ; 
 int SNDRV_PCM_FMTBIT_U8 ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_interval_any (struct snd_interval*) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 

__attribute__((used)) static int hw_rule_playback_channels_by_format(struct snd_pcm_hw_params *params,
					       struct snd_pcm_hw_rule *rule)
{
	struct snd_interval *c = hw_param_interval(params,
						   SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_mask *f = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	struct snd_interval ch;
	u64 fmask;

	snd_interval_any(&ch);
	ch.integer = 1;
	fmask = f->bits[0] + ((u64)f->bits[1] << 32);

	/* S32_BE is mono (and stereo) only */
	if (fmask == SNDRV_PCM_FMTBIT_S32_BE) {
		ch.min = 1;
#ifdef ECHOCARD_HAS_STEREO_BIG_ENDIAN32
		ch.max = 2;
#else
		ch.max = 1;
#endif
	/* U8 is stereo only */
	} else if (fmask == SNDRV_PCM_FMTBIT_U8)
		ch.min = ch.max = 2;
	/* S16_LE and S24_3LE must be at least stereo */
	else if (!(fmask & ~(SNDRV_PCM_FMTBIT_S16_LE |
			       SNDRV_PCM_FMTBIT_S24_3LE)))
		ch.min = 2;
	else
		return 0;

	return snd_interval_refine(c, &ch);
}