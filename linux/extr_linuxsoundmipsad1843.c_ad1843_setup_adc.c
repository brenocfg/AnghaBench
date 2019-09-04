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
struct snd_ad1843 {int dummy; } ;
typedef  int snd_pcm_format_t ;

/* Variables and functions */
#define  SNDRV_PCM_FORMAT_A_LAW 132 
#define  SNDRV_PCM_FORMAT_MU_LAW 131 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_S8 129 
#define  SNDRV_PCM_FORMAT_U8 128 
 int /*<<< orphan*/  ad1843_ADLF ; 
 int /*<<< orphan*/  ad1843_ADRF ; 
 int /*<<< orphan*/  ad1843_C3C ; 
 int /*<<< orphan*/  ad1843_write_bits (struct snd_ad1843*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ad1843_write_multi (struct snd_ad1843*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

void ad1843_setup_adc(struct snd_ad1843 *ad1843,
		      unsigned int framerate,
		      snd_pcm_format_t fmt,
		      unsigned int channels)
{
	int da_fmt = 0;

	switch (fmt) {
	case SNDRV_PCM_FORMAT_S8:	da_fmt = 0; break;
	case SNDRV_PCM_FORMAT_U8:	da_fmt = 0; break;
	case SNDRV_PCM_FORMAT_S16_LE:	da_fmt = 1; break;
	case SNDRV_PCM_FORMAT_MU_LAW:	da_fmt = 2; break;
	case SNDRV_PCM_FORMAT_A_LAW:	da_fmt = 3; break;
	default:		break;
	}

	ad1843_write_bits(ad1843, &ad1843_C3C, framerate);
	ad1843_write_multi(ad1843, 2,
			   &ad1843_ADLF, da_fmt, &ad1843_ADRF, da_fmt);
}