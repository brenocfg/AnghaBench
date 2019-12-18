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
struct snd_cs4231 {int dummy; } ;

/* Variables and functions */
 unsigned char CS4231_ADPCM_16 ; 
 unsigned char CS4231_ALAW_8 ; 
 unsigned char CS4231_LINEAR_16 ; 
 unsigned char CS4231_LINEAR_16_BIG ; 
 unsigned char CS4231_LINEAR_8 ; 
 unsigned char CS4231_STEREO ; 
 unsigned char CS4231_ULAW_8 ; 
#define  SNDRV_PCM_FORMAT_A_LAW 132 
#define  SNDRV_PCM_FORMAT_IMA_ADPCM 131 
#define  SNDRV_PCM_FORMAT_MU_LAW 130 
#define  SNDRV_PCM_FORMAT_S16_BE 129 
#define  SNDRV_PCM_FORMAT_S16_LE 128 

__attribute__((used)) static unsigned char snd_cs4231_get_format(struct snd_cs4231 *chip, int format,
					   int channels)
{
	unsigned char rformat;

	rformat = CS4231_LINEAR_8;
	switch (format) {
	case SNDRV_PCM_FORMAT_MU_LAW:
		rformat = CS4231_ULAW_8;
		break;
	case SNDRV_PCM_FORMAT_A_LAW:
		rformat = CS4231_ALAW_8;
		break;
	case SNDRV_PCM_FORMAT_S16_LE:
		rformat = CS4231_LINEAR_16;
		break;
	case SNDRV_PCM_FORMAT_S16_BE:
		rformat = CS4231_LINEAR_16_BIG;
		break;
	case SNDRV_PCM_FORMAT_IMA_ADPCM:
		rformat = CS4231_ADPCM_16;
		break;
	}
	if (channels > 1)
		rformat |= CS4231_STEREO;
	return rformat;
}