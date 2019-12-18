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
struct snd_ad1816a {int dummy; } ;
typedef  int snd_pcm_format_t ;

/* Variables and functions */
 unsigned char AD1816A_FMT_ALAW_8 ; 
 unsigned char AD1816A_FMT_LINEAR_16_BIG ; 
 unsigned char AD1816A_FMT_LINEAR_16_LIT ; 
 unsigned char AD1816A_FMT_LINEAR_8 ; 
 unsigned char AD1816A_FMT_STEREO ; 
 unsigned char AD1816A_FMT_ULAW_8 ; 
#define  SNDRV_PCM_FORMAT_A_LAW 131 
#define  SNDRV_PCM_FORMAT_MU_LAW 130 
#define  SNDRV_PCM_FORMAT_S16_BE 129 
#define  SNDRV_PCM_FORMAT_S16_LE 128 

__attribute__((used)) static unsigned char snd_ad1816a_get_format(struct snd_ad1816a *chip,
					    snd_pcm_format_t format,
					    int channels)
{
	unsigned char retval = AD1816A_FMT_LINEAR_8;

	switch (format) {
	case SNDRV_PCM_FORMAT_MU_LAW:
		retval = AD1816A_FMT_ULAW_8;
		break;
	case SNDRV_PCM_FORMAT_A_LAW:
		retval = AD1816A_FMT_ALAW_8;
		break;
	case SNDRV_PCM_FORMAT_S16_LE:
		retval = AD1816A_FMT_LINEAR_16_LIT;
		break;
	case SNDRV_PCM_FORMAT_S16_BE:
		retval = AD1816A_FMT_LINEAR_16_BIG;
	}
	return (channels > 1) ? (retval | AD1816A_FMT_STEREO) : retval;
}